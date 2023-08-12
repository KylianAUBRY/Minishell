/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:49:58 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/10 17:01:45 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	if (i > 2)
		return (print_error_message(ERRCODE_CD_ARG));
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
