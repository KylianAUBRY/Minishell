/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:27:03 by kyaubry           #+#    #+#             */
/*   Updated: 2023/07/28 00:34:49 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redir_pipe(char **cmd, int i, t_shell *shell)
{
	while (i > 0 && (cmd[i][0] != PR || cmd[i][1] != '|'))
		i--;
	if (ft_pipe(cmd, i, shell) == 0)
		return (-1);
	if (i == 0)
		i--;
	while (cmd[++i] != NULL && (cmd[i][0] != PR || cmd[i][1] != '|'))
		if (ft_redir_pipe2(cmd, i, shell) == -1)
			return (-1);
	return (0);
}

int	ft_pipe_left(t_shell *shell)
{
	if (shell->pipefd[1] != -1)
		close(shell->pipefd[1]);
	shell->pipefd[1] = -1;
	if (dup2(shell->pipefd[0], STDIN_FILENO) == -1)
	{
		close(shell->pipefd[0]);
		shell->pipefd[0] = -1;
		return (print_error_message(ERRCODE_DUP2));
	}
	return (0);
}

int	ft_pipe_right(t_shell *shell)
{
	if (shell->pipefd_after[0] != -1)
		close(shell->pipefd_after[0]);
	shell->pipefd_after[0] = -1;
	if (dup2(shell->pipefd_after[1], STDOUT_FILENO) == -1)
	{
		close(shell->pipefd_after[1]);
		shell->pipefd_after[1] = -1;
		return (print_error_message(ERRCODE_DUP2));
	}
	return (0);
}

int	ft_pipe(char **cmd, int j, t_shell *shell)
{
	if (j > 0 && cmd[j][0] == PR && cmd[j][1] == '|')
		if (ft_pipe_left(shell) == 1)
			return (0);
	while (cmd[++j] != NULL)
		if (cmd[j][0] == PR && cmd[j][1] == '|')
			break ;
	if (cmd[j] != NULL && cmd[j][0] == PR && cmd[j][1] == '|')
		if (ft_pipe_right(shell) == 1)
			return (0);
	return (1);
}

int	ft_open_pipe(t_shell *shell, char **cmd, int j)
{
	while (cmd[++j] != NULL)
		if (cmd[j][0] == PR && cmd[j][1] == '|')
			break ;
	if (cmd[j] != NULL && cmd[j][0] == PR && cmd[j][1] == '|')
	{
		if (pipe(shell->pipefd_after) == -1)
		{
			shell->pipefd_after[0] = -1;
			shell->pipefd_after[1] = -1;
			return (print_error_message(ERRCODE_PIPE));
		}
	}
	return (1);
}
