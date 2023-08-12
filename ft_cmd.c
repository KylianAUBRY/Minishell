/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:24:23 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/11 16:32:26 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_cmd(char **cmd, int j, t_shell *shell, char **envp)
{
	pid_t	pid;
	char	**args;
	int		status;

	if (ft_open_pipe(shell, cmd, j) == 0)
		return (0);
	pid = fork();
	if (pid < 0)
		return (print_error_message(ERRCODE_PID));
	if (pid == 0)
	{
		args = ft_fill_tab(cmd, j);
		if (!args)
			return (ft_free_error_exec(cmd, shell, args));
		shell->fd = ft_redir_pipe(cmd, j, shell);
		if (shell->fd != -1)
			execve(args[0], args, envp);
		return (ft_free_error_exec(cmd, shell, args));
	}
	waitpid(pid, &status, 0);
	shell->var_global.temp2 = status;
	ft_close_fd(shell);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (print_error_message(ERRCODE_PROC));
	return (shell->var_global.temp2);
}

int	ft_cmd_erreur(char **cmd, int i)
{
	ft_print_error(cmd[i] + 1);
	ft_print_error(": command not found\n");
	return (127);
}

void	ft_cmd(char **cmd, t_shell *shell, char **envp)
{
	int	i;
	int	status;

	i = -1;
	if (!cmd)
		return ;
	status = 0;
	while (cmd[++i] != NULL)
	{
		g_int_temp = 1;
		if (cmd[i][0] == CMD)
			status = ft_exec_cmd(cmd, i, shell, envp);
		else if (cmd[i][0] == CMDCUSTOM && ft_check_pipe(cmd) == 1)
			status = execvp_custom(cmd, i, shell);
		else if (cmd[i][0] == CMDCUSTOM)
			status = ft_exec_custom_no_pipe(cmd, i, shell);
		else if (cmd[i][0] == ERR)
			status = ft_cmd_erreur(cmd, i);
		g_int_temp = 0;
	}
	if (i > 0)
		shell->var_global.res = status;
}
