/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:57:10 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/12 16:52:46 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_and_return(char **tab)
{
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[++j])
		{
			if (ft_strcmp(tab[i], tab[j]) < 0)
				ft_swap_val(&tab[i], &tab[j]);
		}
	}
	i = -1;
	while (tab[++i] != NULL)
	{
		if (tab[i][ft_strlen(tab[i]) - 1] != '=')
			printf("declare -x %s\n", tab[i]);
		free(tab[i]);
	}
	free(tab);
	return (0);
}

int	ft_export_no_args(t_shell *shell)
{
	int		j;
	char	**tab;

	j = 0;
	while (shell->var_global.tab[j])
		j++;
	tab = malloc(sizeof(char *) * (j + 2));
	if (!tab)
		return (1);
	j = -1;
	while (shell->var_global.tab[++j])
	{
		tab[j] = ft_strdup_join(shell->var_global.tab[j][0],
			shell->var_global.tab[j][1]);
		if (!tab)
			return (ft_free_line_export(tab));
	}
	tab[j] = NULL;
	return (print_and_return(tab));
}

char	***fill_last_tab_2(char ***tab, int i, t_shell *shell)
{
	while (shell->var_global.tab[i] != NULL)
	{
		tab[i + 1][0] = ft_strdup(shell->var_global.tab[i][0]);
		if (!tab[i + 1][0])
			return (ft_free_line_all(tab));
		tab[i + 1][1] = ft_strdup(shell->var_global.tab[i][1]);
		if (!tab[i + 1][1])
			return (ft_free_line_all(tab));
		i++;
	}
	return (tab);
}

char	***fill_last_tab(char ***tab, char *name, char *val, t_shell *shell)
{
	int	i;

	i = shell->i;
	if (shell->var_global.tab[i] == NULL)
	{
		tab[i][0] = ft_strdup(name);
		if (!tab[i][0])
			return (ft_free_line_all(tab));
		tab[i][1] = ft_strdup(val);
		if (!tab[i][1])
			return (ft_free_line_all(tab));
		return (tab);
	}
	return (tab);
}
