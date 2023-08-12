/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:06:46 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/12 13:05:29 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_chr_tab(char *name, t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->var_global.tab[++i] != NULL)
	{
		if (ft_strcmp(shell->var_global.tab[i][0], name) == 0)
			return (1);
	}
	return (0);
}

int	ft_replace_val(char *name, char **args, int k, t_shell *shell)
{
	int	i;
	int	j;

	j = shell->i;
	i = -1;
	if (args[k][j] == '=')
		j++;
	while (shell->var_global.tab[++i] != NULL)
	{
		if (ft_strcmp(shell->var_global.tab[i][0], name) == 0)
		{
			free(shell->var_global.tab[i][1]);
			shell->var_global.tab[i][1] = ft_strdup(args[k] + j);
			if (!shell->var_global.tab[i][1])
				return (print_error_message(ERRCODE_MALLOC));
			break ;
		}
	}
	return (0);
}

int	ft_export_2(char *name, char **args, int k, t_shell *shell)
{
	int		j;
	char	*val;

	while (args[k][++shell->i] != '\0' && args[k][shell->i] != '=')
		name[shell->i] = args[k][shell->i];
	name[shell->i] = '\0';
	if (ft_chr_tab(name, shell) != 0)
		return (ft_replace_val(name, args, k, shell));
	if (args[k][shell->i] == '=')
		shell->i++;
	j = shell->i;
	while (args[k][shell->i] != '\0')
		shell->i++;
	val = malloc(sizeof(char) * (shell->i - j) + 1);
	if (!val)
		return (print_error_message(ERRCODE_MALLOC));
	shell->i = 0;
	while (args[k][j] != '\0')
	{
		val[shell->i] = args[k][j];
		shell->i++;
		j++;
	}
	val[shell->i] = '\0';
	return (ft_export_3(name, val, shell));
}

int	ft_export_no_val(char *name, char **args, int k, t_shell *shell)
{
	char	*val;
	int		i;

	i = -1;
	while (args[k][++i] != '\0' && args[k][i] != '=')
		name[i] = args[k][i];
	name[i] = '\0';
	if (ft_chr_tab(name, shell) != 0)
	{
		shell->i = i;
		return (ft_replace_val(name, args, k, shell));
	}
	val = ft_strdup("");
	if (!val)
		return (1);
	return (ft_export_3(name, val, shell));
}

int	ft_export(char **args, t_shell *shell)
{
	int		i;
	char	*name;
	int		j;

	j = 0;
	while (args[++j] != NULL)
	{
		shell->i = -1;
		i = 0;
		while (args[j][i] != '\0' && args[j][i] != '=')
			i++;
		if (i == 0)
			return (print_error_message(ERRCODE_EXPORT_VALUE));
		name = malloc(sizeof(char) * i + 1);
		if (!name)
			return (print_error_message(ERRCODE_MALLOC));
		if (args[j][i] == '=')
			i = ft_export_2(name, args, j, shell);
		else
			i = ft_export_no_val(name, args, j, shell);
		free(name);
	}
	if (j <= 1)
		return (ft_export_no_args(shell));
	return (i);
}
