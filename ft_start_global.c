/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_global.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 00:07:23 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/12 14:42:42 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_delim(const char *s, char c)
{
	char	*dest;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != c)
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_free_tab(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->var_global.tab[++i])
	{
		if (!shell->var_global.tab[i][0])
			break ;
		free(shell->var_global.tab[i][0]);
		if (!shell->var_global.tab[i][1])
			break ;
		free(shell->var_global.tab[i][1]);
	}
	i = -1;
	while (shell->var_global.tab[++i])
	{
		free(shell->var_global.tab[i]);
	}
	free(shell->var_global.tab[i]);
	return (0);
}

int	ft_free_global_i(int i, t_shell *shell)
{
	while (--i >= 0)
		free(shell->var_global.tab[i]);
	free(shell->var_global.tab);
	return (0);
}

int	ft_fill_tab_env(char **envp, t_shell *shell)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		shell->var_global.tab[i] = malloc(sizeof(char *) * 2);
		if (!shell->var_global.tab[i])
			return (ft_free_global_i(i, shell));
	}
	shell->var_global.tab[i] = NULL;
	i = -1;
	while (envp[++i])
	{
		shell->var_global.tab[i][0] = ft_strdup_delim(envp[i], '=');
		if (!shell->var_global.tab[i][0])
			return (ft_free_tab(shell));
		shell->var_global.tab[i][1] = ft_strdup(envp[i]
				+ ft_strlen_char(envp[i], '=') + 1);
		if (!shell->var_global.tab[i][1])
			return (ft_free_tab(shell));
	}
	shell->var_global.tab[i] = NULL;
	return (1);
}

int	ft_start_global(char **envp, t_shell *shell)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	shell->var_global.tab = malloc(sizeof(char **) * (i + 1));
	if (!shell->var_global.tab)
		return (0);
	shell->var_global.res = 0;
	shell->var_global.res_tmp = 0;
	return (ft_fill_tab_env(envp, shell));
}
