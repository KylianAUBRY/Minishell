/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:58:09 by kylian            #+#    #+#             */
/*   Updated: 2023/08/10 17:02:41 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
(str[i] == '>' && str[i + 1] == '>' && (str[i + 2] == '|' || str[i + 2] == '<'
		|| str[i + 2] == '>'))
(str[i] == '>' && str[i + 1] == '>' && str[i + 2] == ' ' && (str[i + 3] == '|'
		|| str[i + 3] == '<' || str[i + 3] == '>'))
(str[i] == '>' && str[i + 1] == '<')
(str[i] == '>' && (str[i + 1] == ' ' && (str[i + 2] == '|' || str[i + 2] == '<'
			|| str[i + 2] == '>')))

(str[i] == '<' && str[i + 1] == '<' && (str[i + 2] == '|' || str[i + 2] == '<'
		|| str[i + 2] == '>'))
(str[i] == '<' && str[i + 1] == '<' && str[i + 2] == ' ' && (str[i + 3] == '|'
		|| str[i + 3] == '<' || str[i + 3] == '>'))
(str[i] == '<' && (str[i + 1] == ' ' && (str[i + 2] == '|' || str[i + 2] == '<'
			|| str[i + 2] == '>')))
(str[i] == '<' && (str[i + 1] == '>' && (str[i + 2] == '>' || str[i + 2] == '<'
			|| str[i + 2] == '|')))
(str[i] == '<' && str[i + 1] == '>' && str[i + 2] == ' ' && (str[i + 3] == '>'
		|| str[i + 3] == '<' || str[i + 3] == '|'))*/

int	ft_verif_order_pipe_space(char *str, int i)
{
	int	j;

	if (str[i] == '<' && str[i + 1] == '<')
	{
		j = ft_pass_space(str, i + 2);
		if (j != i + 2 && (str[j] == '|' || str[j] == '<' || str[j] == '>'))
			return (1);
	}
	if (str[i] == '<')
	{
		j = ft_pass_space(str, i + 1);
		if (j != i + 1 && (str[j] == '|' || str[j] == '<' || str[j] == '>'))
			return (1);
	}
	if (str[i] == '<' && str[i + 1] == '>')
	{
		j = ft_pass_space(str, i + 2);
		if (j != i + 2 && (str[j] == '>' || str[j] == '<' || str[j] == '|'))
			return (1);
	}
	return (0);
}

int	ft_verif_order_pipe_2(char *str, int i)
{
	int	j;

	if (str[i] == '>' && str[i + 1] == '>' && (str[i + 2] == '|'
			|| str[i + 2] == '<' || str[i + 2] == '>'))
		return (1);
	if (str[i] == '>' && str[i + 1] == '<')
		return (1);
	if (str[i] == '<' && str[i + 1] == '<' && (str[i + 2] == '|'
			|| str[i + 2] == '<' || str[i + 2] == '>'))
		return (1);
	if (str[i] == '<' && (str[i + 1] == '>' && (str[i + 2] == '>'
				|| str[i + 2] == '<' || str[i + 2] == '|')))
		return (1);
	if (str[i] == '|')
	{
		j = ft_pass_space(str, i + 1);
		if (str[i + 1] == '|' || (j != i + 1 && str[j] == '|'))
			return (1);
	}
	return (0);
}

int	ft_verif_order_pipe(char *str, int i)
{
	int	j;

	if (str[i] != '>' && str[i] != '<' && str[i] != '|')
		return (0);
	if (ft_verif_order_pipe_2(str, i) == 1)
		return (1);
	if (str[i] == '>' && str[i + 1] == '>')
	{
		j = ft_pass_space(str, i + 2);
		if (j != i + 2 && (str[j] == '|' || str[j] == '<' || str[j] == '>'))
			return (1);
	}
	if (str[i] == '>')
	{
		j = ft_pass_space(str, i + 1);
		if (j != i + 1 && (str[j] == '|' || str[j] == '<' || str[j] == '>'))
			return (1);
	}
	return (ft_verif_order_pipe_space(str, i));
}

int	ft_verif_redir_2(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '|')
		return (print_error_message(ERRCODE_REDIR_ALL));
	while (str[++i] && (str[i] == ' ' || str[i] == '\t'))
		;
	if (str[0] == '|' || str[i] == '|')
		return (print_error_message(ERRCODE_REDIR_ALL));
	i = -1;
	while (str[++i])
	{
		if (ft_verif_order_pipe(str, i) == 1)
			return (print_error_message(ERRCODE_REDIR_ALL));
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == '\"')
			while (str[++i] && str[i] != '\"')
				;
	}
	return (0);
}

int	ft_verif_redir(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		while (str[i] && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
		{
			i++;
			j++;
		}
		if (j > 3)
			return (print_error_message(ERRCODE_REDIR_ALL));
		j = 0;
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == '\"')
			while (str[++i] && str[i] != '\"')
				;
	}
	return (ft_verif_redir_2(str));
}
