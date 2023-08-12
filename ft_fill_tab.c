/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:26:33 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/01 16:47:39 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_error_fill_tab(char **args, int j)
{
	while (--j >= 0)
		free(args[j]);
	free(args);
	print_error_message(ERRCODE_MALLOC);
	return (NULL);
}

char	**ft_fill_valu(char **cmd, int i, char **args)
{
	int	j;

	j = 0;
	while (cmd[++i] != NULL && (cmd[i][0] != PR || cmd[i][1] != '|'))
	{
		if (cmd[i][0] != PR && (i == 0 || (cmd[i - 1][0] != PR || cmd[i
					- 1][1] == '|')))
		{
			args[j] = ft_strdup(cmd[i] + 1);
			if (!args[j])
				return (ft_error_fill_tab(args, j));
			j++;
		}
	}
	args[j] = NULL;
	return (args);
}

char	**ft_fill_tab(char **cmd, int j)
{
	char	**args;
	int		i;

	i = j;
	if (!cmd)
		return (NULL);
	while (cmd[++i] != NULL)
	{
		if (cmd[i][0] == PR && cmd[i][1] == '|')
			break ;
	}
	args = malloc(sizeof(char *) * (i - j + 2));
	if (!args)
		return (NULL);
	i = j - 1;
	return (ft_fill_valu(cmd, i, args));
}
