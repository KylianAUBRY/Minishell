/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:14:57 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/11 16:51:04 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->var_global.tab[++i])
	{
		printf("%s", shell->var_global.tab[i][0]);
		if (shell->var_global.tab[i][1])
			printf("=%s", shell->var_global.tab[i][1]);
		printf("\n");
	}
	return (0);
}
