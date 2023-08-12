/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:28:48 by event             #+#    #+#             */
/*   Updated: 2023/08/12 12:37:54 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i] != NULL)
		free(cmd[i]);
	free(cmd);
}

void	ft_close_fd(t_shell *shell)
{
	if (shell->pipefd[0] != -1)
		close(shell->pipefd[0]);
	shell->pipefd[0] = -1;
	if (shell->pipefd[1] != -1)
		close(shell->pipefd[1]);
	shell->pipefd[1] = -1;
	if (shell->pipefd_after[1] != -1)
		close(shell->pipefd_after[1]);
	shell->pipefd_after[1] = -1;
	if (shell->pipefd_after[0] != -1)
		shell->pipefd[0] = shell->pipefd_after[0];
	shell->pipefd_after[0] = -1;
}

void	free_global(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->var_global.tab[++i] != NULL)
	{
		if (shell->var_global.tab[i][0])
			free(shell->var_global.tab[i][0]);
		if (shell->var_global.tab[i][1])
			free(shell->var_global.tab[i][1]);
		free(shell->var_global.tab[i]);
	}
	free(shell->var_global.tab);
}

int	for_25_line(char **args, t_shell *shell)
{
	int	i;

	i = -1;
	if (args)
	{
		while (args[++i] != NULL)
			free(args[i]);
		free(args);
	}
	free_global(shell);
	i = shell->var_global.res_tmp;
	free(shell);
	exit(i);
	return (i);
}

int	ft_free_error_exec(char **cmd, t_shell *shell, char **args)
{
	int	i;

	if (shell->pipefd[0] != -1)
		close(shell->pipefd[0]);
	if (shell->pipefd[1] != -1)
		close(shell->pipefd[1]);
	if (shell->pipefd_after[0] != -1)
		close(shell->pipefd_after[0]);
	if (shell->pipefd_after[1] != -1)
		close(shell->pipefd_after[1]);
	if (shell->fd_enter != -1)
		close(shell->fd_enter);
	if (shell->fd_exit != -1)
		close(shell->fd_exit);
	shell->fd_exit = -1;
	shell->fd_enter = -1;
	i = -1;
	while (cmd[++i] != NULL)
		free(cmd[i]);
	free(cmd);
	return (for_25_line(args, shell));
}
