/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:04:05 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/12 14:25:39 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp_n(char *args)
{
	int	i;

	i = 0;
	if (args && args[i] == '-')
		i++;
	else
		return (1);
	if (args && args[i] == '\0')
		return (1);
	while (args && args[i] && args[i] == 'n')
		i++;
	if (args && args[i] == '\0')
		return (0);
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	j;

	i = 1;
	if (!args || !args[0] || !args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (ft_strcmp_n(args[i]) == 0)
		i++;
	j = i;
	if (i == 2 && !args[2])
		return (0);
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		i++;
		if (args[i] != NULL)
			printf(" ");
	}
	if (j == 1)
		printf("\n");
	return (0);
}
