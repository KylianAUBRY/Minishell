/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:19:11 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/10 17:01:57 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_nb(int n)
{
	int	t;

	t = 0;
	if (n <= 0)
		t++;
	while (n != 0)
	{
		n /= 10;
		t++;
	}
	return (t);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		i;
	long	nb;

	i = count_nb(n) - 1;
	nb = n;
	dest = malloc(sizeof(char) * (count_nb(n) + 1));
	if (!dest)
		return (NULL);
	if (nb < 0)
	{
		dest[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		dest[0] = '0';
	while (nb != 0)
	{
		dest[i] = (nb % 10) + '0';
		i--;
		nb /= 10;
	}
	dest[count_nb(n)] = '\0';
	return (dest);
}
