/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_custom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:23:19 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/11 16:51:47 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_cmd_custom(char **args, char **cmd, t_shell *shell)
{
	if (!args[0])
		return (0);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, shell));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, shell));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(shell));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args, cmd, shell));
	return (0);
}

int	execvp_custom(char **cmd, int j, t_shell *shell)
{
	char	**args;
	int		status;
	pid_t	pid;

	status = 0;
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
			shell->var_global.res_tmp = ft_exec_cmd_custom(args, cmd, shell);
		return (ft_free_error_exec(cmd, shell, args));
	}
	waitpid(pid, &status, 0);
	ft_close_fd(shell);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		print_error_message(ERRCODE_PROC);
	return (status);
}

int	ft_check_pipe(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i] != NULL)
	{
		if (cmd[i][0] == PR && cmd[i][1] == '|')
			return (1);
	}
	return (0);
}

int	ft_close_custom(char **args, int saved_stdin, int saved_stdout, int status)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		close(saved_stdin);
		close(saved_stdout);
		return (print_error_message(ERRCODE_DUP2));
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		close(saved_stdin);
		close(saved_stdout);
		return (print_error_message(ERRCODE_DUP2));
	}
	close(saved_stdin);
	close(saved_stdout);
	ft_free_cmd(args);
	return (status);
}

int	ft_exec_custom_no_pipe(char **cmd, int i, t_shell *shell)
{
	char	**args;
	int		status;
	int		saved_stdin;
	int		saved_stdout;

	args = ft_fill_tab(cmd, i);
	if (!args)
		return (1);
	if (ft_strcmp(args[0], "echo") == 0 || ft_strcmp(args[0], "pwd") == 0
		|| ft_strcmp(args[0], "env") == 0)
	{
		ft_free_cmd(args);
		return (execvp_custom(cmd, i, shell));
	}
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (print_error_message(ERRCODE_DUP));
	status = 0;
	shell->fd = ft_redir_pipe(cmd, i, shell);
	if (shell->fd != -1)
		status = ft_exec_cmd_custom(args, cmd, shell);
	if (shell->fd != 0 && shell->fd != -1)
		close(shell->fd);
	return (ft_close_custom(args, saved_stdin, saved_stdout, status));
}
