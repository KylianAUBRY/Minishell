/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chevron_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:41:40 by kyaubry           #+#    #+#             */
/*   Updated: 2023/07/28 00:34:36 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_duble_chevron(char **cmd, int i)
{
	int	fd;

	fd = 0;
	if (cmd[i] != NULL)
	{
		fd = open(cmd[i] + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			print_error_message(ERRCODE_FD);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	ft_right_chevron_apped(char **cmd, int i, t_shell *shell)
{
	int	fd;

	fd = 0;
	if (cmd[i] != NULL)
	{
		fd = open(cmd[i] + 1, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			print_error_message(ERRCODE_FD);
			return (-1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			print_error_message(ERRCODE_DUP2);
			return (-1);
		}
	}
	if (shell->fd_exit != -1)
		close(shell->fd_exit);
	shell->fd_enter = fd;
	return (fd);
}

int	ft_redir_pipe2(char **cmd, int i, t_shell *shell)
{
	if (cmd[i][0] == PR && cmd[i][1] == '>' && cmd[i][2] == '>')
		return (ft_right_chevron_apped(cmd, i + 1, shell));
	else if (cmd[i][0] == PR && cmd[i][1] == '>')
		return (ft_right_chevron(cmd, i + 1, shell));
	else if (cmd[i][0] == PR && cmd[i][1] == '<' && cmd[i][2] == '<')
		return (ft_left_chevron_delimiter(cmd, i + 1, shell));
	else if (cmd[i][0] == PR && cmd[i][1] == '<' && cmd[i][2] == '>')
		return (ft_duble_chevron(cmd, i + 1));
	else if (cmd[i][0] == PR && cmd[i][1] == '<')
		return (ft_left_chevron(cmd, i + 1, shell));
	return (0);
}
