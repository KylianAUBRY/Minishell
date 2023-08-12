/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:53:55 by kylian            #+#    #+#             */
/*   Updated: 2023/08/11 16:26:19 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ========== function to quit the shell ========== */
int	ft_leave_shell(t_shell *shell)
{
	free_global(shell);
	free(shell);
	rl_clear_history();
	exit(0);
}
