/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:32:16 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/11 15:14:24 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_error_custom(char *src)
{
	int	i;

	i = -1;
	if (!src || !src[0])
		return (1);
	while (src[++i])
		write(2, &src[i], 1);
	return (1);
}

void	ft_print_error(char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		write(2, &src[i], 1);
}

int	print_error_message_2(int error_code)
{
	if (error_code == ERRCODE_DOUBLE_QUOT)
		ft_print_error(ERRMSG_DOUBLE_QUOT);
	else if (error_code == ERRCODE_SYNTAX)
	{
		ft_print_error("minishell: ");
		ft_print_error(ERRMSG_SYNTAX);
	}
	else if (error_code == ERRCODE_REDIR_ALL)
	{
		ft_print_error("minishell: ");
		ft_print_error(ERRMSG_REDIR_ALL);
	}
	return (1);
}

int	print_error_message(int error_code)
{
	if (error_code == ERRCODE_MALLOC)
		ft_print_error(ERRMSG_MALLOC);
	else if (error_code == ERRCODE_READ)
		ft_print_error(ERRMSG_READ);
	else if (error_code == ERRCODE_PIPE)
		ft_print_error(ERRMSG_PIPE);
	else if (error_code == ERRCODE_PID)
		ft_print_error(ERRMSG_PID);
	else if (error_code == ERRCODE_EXEC)
		ft_print_error(ERRMSG_EXEC);
	else if (error_code == ERRCODE_FD)
		ft_print_error(ERRMSG_FD);
	else if (error_code == ERRCODE_DUP2)
		ft_print_error(ERRMSG_DUP2);
	else if (error_code == ERRCODE_DUP)
		ft_print_error(ERRMSG_DUP);
	else if (error_code == ERRCODE_GETCWD)
		ft_print_error(ERRMSG_GETCWD);
	else if (error_code == ERRCODE_EXPORT_VALUE)
		ft_print_error(ERRMSG_EXPORT_VALUE);
	else if (error_code == ERRCODE_CD_ARG)
		ft_print_error(ERRMSG_CD_ARG);
	else if (error_code == ERRCODE_SINGLE_QUOT)
		ft_print_error(ERRMSG_SINGLE_QUOT);
	return (print_error_message_2(error_code));
}

void	print_error_message_void(int error_code)
{
	if (error_code == ERRCODE_MALLOC)
		ft_print_error(ERRMSG_MALLOC);
	else if (error_code == ERRCODE_REDIR_ALL)
	{
		ft_print_error("minishell: ");
		ft_print_error(ERRMSG_REDIR_ALL);
	}
}
