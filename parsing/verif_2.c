/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 23:11:24 by kylian            #+#    #+#             */
/*   Updated: 2023/08/12 15:01:21 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_verif_meta_char(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == '\"')
			while (str[++i] && str[i] != '\"')
				;
		if (str[i] == '\\' || str[i] == '(' || str[i] == ')' || str[i] == '['
			|| str[i] == '{' || str[i] == '^')
		{
			write(2, &str[i], 1);
			return (ft_print_error_custom(" is a non-acceptable character\n"));
		}
	}
	return (ft_verif_redir(str));
}

int	ft_verif_syntax(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i])
				if (str[i] == '\'')
					break ;
			if (str[i] == '\0')
				return (print_error_message(ERRCODE_SINGLE_QUOT));
		}
		if (str[i] == '\"')
		{
			while (str[++i] && str[i] != '\"')
				if (str[i] == '\"')
					break ;
			if (str[i] == '\0')
				return (print_error_message(ERRCODE_DOUBLE_QUOT));
		}
		if (!str[i])
			break ;
		i++;
	}
	if (str[i - 1] == '>' || str[i - 1] == '<')
		return (print_error_message(ERRCODE_SYNTAX));
	return (ft_verif_meta_char(str));
}
