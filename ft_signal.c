/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:46:56 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/12 13:23:16 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pipe_leave(char *dest, t_shell *shell)
{
	add_history(dest + 1);
	if (dest[0] == PCD)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		free(dest);
		ft_leave_shell(shell);
	}
	free(dest);
}

void	sig_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		if (g_int_temp != 1)
			rl_on_new_line();
		else
		{
			write(1, "\0", 1);
			g_int_temp = 0;
		}
		rl_redisplay();
	}
}
