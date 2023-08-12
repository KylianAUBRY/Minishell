/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:47:34 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/11 16:49:52 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	***ft_free_line(char ***tab)
{
	int	i;

	i = -1;
	while (tab[++i] != NULL)
		free(tab[i]);
	free(tab);
	return (NULL);
}

char	***ft_free_line_all(char ***tab)
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
	return (NULL);
}

char	***reffel_tab(char ***tab, char *name, char *val, t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->var_global.tab[++i] != NULL)
	{
		if (ft_strcmp(shell->var_global.tab[i][0], name) > 0)
		{
			tab[i][0] = ft_strdup(name);
			if (!tab[i][0])
				return (ft_free_line_all(tab));
			tab[i][1] = ft_strdup(val);
			if (!tab[i][1])
				return (ft_free_line_all(tab));
			return (fill_last_tab_2(tab, i, shell));
		}
		tab[i][0] = ft_strdup(shell->var_global.tab[i][0]);
		if (!tab[i][0])
			return (ft_free_line_all(tab));
		tab[i][1] = ft_strdup(shell->var_global.tab[i][1]);
		if (!tab[i][1])
			return (ft_free_line_all(tab));
	}
	shell->i = i;
	return (fill_last_tab(tab, name, val, shell));
}

char	***malloc_tab(char *name, char *val, t_shell *shell)
{
	char	***tab;
	int		i;
	int		j;

	i = 0;
	while (shell->var_global.tab[i] != NULL)
		i++;
	tab = malloc(sizeof(char ***) * (i + 2));
	if (!tab)
		return (NULL);
	j = i + 1;
	while (i >= 0)
	{
		tab[i] = malloc(sizeof(char ***) * 2);
		if (!tab[i])
			return (ft_free_line(tab));
		tab[i][0] = NULL;
		tab[i][1] = NULL;
		i--;
	}
	tab[j] = NULL;
	return (reffel_tab(tab, name, val, shell));
}

int	ft_export_3(char *name, char *val, t_shell *shell)
{
	char	***tab;

	tab = malloc_tab(name, val, shell);
	free(val);
	if (!tab)
		return (print_error_message(ERRCODE_MALLOC));
	ft_free_line_all(shell->var_global.tab);
	shell->var_global.tab = tab;
	return (0);
}
