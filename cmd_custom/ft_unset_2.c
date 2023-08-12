/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:11:43 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/12 15:12:02 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_int_tab(char *name, t_shell *shell)
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
