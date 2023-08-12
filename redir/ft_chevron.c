/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chevron.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:25:14 by kyaubry           #+#    #+#             */
/*   Updated: 2023/07/27 23:47:05 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_document(char *line, int fd, char *delim)
{
	int	i;

	i = 0;
	while (line[i] && delim[i] && line[i] == delim[i])
		i++;
	if ((!line[i] || line[i] == '\n') && !delim[i])
		return (0);
	i = -1;
	while (line[++i])
		write(fd, &line[i], 1);
	return (1);
}

int	ft_right_chevron(char **cmd, int i, t_shell *shell)
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

int	ft_left_chevron(char **cmd, int i, t_shell *shell)
{
	int	fd;

	fd = 0;
	if (cmd[i] != NULL)
	{
		fd = open(cmd[i] + 1, O_RDONLY);
		if (fd == -1)
		{
			ft_print_error("no such file or directory: ");
			ft_print_error(cmd[i] + 1);
			write(2, "\n", 1);
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			print_error_message(ERRCODE_DUP2);
			return (-1);
		}
	}
	if (shell->fd_enter != -1)
		close(shell->fd_enter);
	shell->fd_enter = fd;
	return (fd);
}

int	ft_re_open(int fd)
{
	close(fd);
	fd = open("temporary_file01", O_RDONLY);
	if (fd == -1)
	{
		print_error_message(ERRCODE_FD);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		print_error_message(ERRCODE_DUP2);
		return (-1);
	}
	return (fd);
}

int	ft_left_chevron_delimiter(char **cmd, int i, t_shell *shell)
{
	int	fd;

	fd = 0;
	if (cmd[i] != NULL)
	{
		fd = open("temporary_file01", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			print_error_message(ERRCODE_FD);
			return (-1);
		}
		while (fill_document(get_next_line(0), fd, cmd[i] + 1) == 1)
			;
		fd = ft_re_open(fd);
		if (fd == -1)
			return (-1);
	}
	if (shell->fd_enter != -1)
		close(shell->fd_enter);
	shell->fd_enter = fd;
	return (fd);
}
