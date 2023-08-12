/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:24:22 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/11 16:57:46 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_int_temp;

int	ft_finish_pipe(char *dest)
{
	int	i;

	i = 0;
	if (!dest || !dest[0])
		return (0);
	while (dest[i])
		i++;
	if (dest[i - 1] == '|')
		return (1);
	i--;
	while (i >= 0 && (dest[i] == ' ' || dest[i] == '\t'))
		i--;
	if (dest[i] == '|')
		return (1);
	return (0);
}

int	ft_chr_pipe_start(char *dest)
{
	int	i;

	i = 0;
	if (!dest || !dest[0])
		return (0);
	if (dest[0] == '|' || ((dest[0] == ' ' || dest[0] == '\t')
			&& dest[1] == '|'))
	{
		add_history(dest);
		free(dest);
		return (1);
	}
	while (dest[i] && (dest[i] == ' ' || dest[i] == '\t'))
		i++;
	if (dest[i] == '|')
	{
		add_history(dest);
		free(dest);
		return (1);
	}
	return (0);
}

void	new_cmd(t_shell *shell, char **envp, char *dest)
{
	char	**cmd;

	cmd = NULL;
	if (ft_chr_pipe_start(dest) == 1)
		return (print_error_message_void(ERRCODE_REDIR_ALL));
	while (ft_finish_pipe(dest) == 1)
	{
		dest = ft_strjoin_modif_pipe(dest, readline("> "));
		if (!dest)
			return (print_error_message_void(ERRCODE_MALLOC));
		if (dest[0] == PCC || dest[0] == PCD)
			return (cmd_pipe_leave(dest, shell));
	}
	if (dest && dest[0])
		add_history(dest);
	cmd = split_master(dest, shell);
	if (cmd != NULL && cmd[0] != NULL)
	{
		ft_cmd(cmd, shell, envp);
		ft_free_cmd(cmd);
	}
	else
		shell->var_global.res = 2;
	free(dest);
}

int	ft_prompt(t_shell *shell, char **envp)
{
	char	*dest;

	signal(SIGINT, sig_ctrl);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		dest = readline("minishell > ");
		if (dest)
			new_cmd(shell, envp, dest);
		else
			return (ft_leave_shell(shell));
		g_int_temp = 0;
		shell->var_global.res_tmp = 0;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (print_error_message(ERRCODE_MALLOC));
	if (ft_start_global(envp, shell) == 0)
	{
		free(shell);
		return (print_error_message(ERRCODE_MALLOC));
	}
	shell->fd_exit = -1;
	shell->fd_enter = -1;
	shell->pipefd[0] = -1;
	shell->pipefd[1] = -1;
	shell->pipefd_after[0] = -1;
	shell->pipefd_after[1] = -1;
	g_int_temp = 0;
	ft_prompt(shell, envp);
}
