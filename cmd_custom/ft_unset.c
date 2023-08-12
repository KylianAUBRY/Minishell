/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:23:52 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/11 16:50:51 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_free_line_unset(char ***tab)
{
	int	i;

	i = -1;
	while (tab[++i] != NULL)
		free(tab[i]);
	free(tab);
	return (1);
}

int	ft_free_line_all_unset(char ***tab)
{
	int	i;

	i = -1;
	while (tab[++i] != NULL)
	{
		if (tab[i][0])
			free(tab[i][0]);
		if (tab[i][1])
			free(tab[i][1]);
		free(tab[i]);
	}
	free(tab);
	return (1);
}

static int	new_tab(char ***tab, char *name, t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (shell->var_global.tab[++i] != NULL)
	{
		if (ft_strcmp(shell->var_global.tab[i][0], name) == 0)
			j--;
		else
		{
			tab[j][0] = ft_strdup(shell->var_global.tab[i][0]);
			if (!tab[j][0])
				return (ft_free_line_all_unset(tab));
			tab[j][1] = ft_strdup(shell->var_global.tab[i][1]);
			if (!tab[j][1])
				return (ft_free_line_all_unset(tab));
		}
		j++;
	}
	tab[j] = NULL;
	ft_free_line_all_unset(shell->var_global.tab);
	shell->var_global.tab = tab;
	return (0);
}

static int	ft_unset_2(char *name, t_shell *shell)
{
	char	***tab;
	int		i;
	int		j;

	i = 0;
	while (shell->var_global.tab[i] != NULL)
		i++;
	tab = malloc(sizeof(char ***) * (i));
	if (!tab)
		return (1);
	i--;
	j = i;
	while (--i >= 0)
	{
		tab[i] = malloc(sizeof(char ***) * 2);
		if (!tab[i])
			return (ft_free_line_unset(tab));
		tab[i][0] = NULL;
		tab[i][1] = NULL;
	}
	tab[j] = NULL;
	return (new_tab(tab, name, shell));
}

int	ft_unset(char **args, t_shell *shell)
{
	char	*name;
	int		j;
	int		i;

	j = 0;
	while (args[++j] != NULL)
	{
		i = 0;
		while (args[j][i] != '\0' && args[j][i] != ' ')
			i++;
		name = malloc(sizeof(char) * i + 1);
		if (!name)
			return (print_error_message(ERRCODE_MALLOC));
		i = -1;
		while (args[j][++i] != '\0' && args[j][i] != ' ')
			name[i] = args[j][i];
		name[i] = '\0';
		i = ft_unset_2(name, shell);
		free(name);
		if (i == 1)
			return (print_error_message(ERRCODE_MALLOC));
	}
	return (i);
}
