/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttofil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:31:09 by ttofil            #+#    #+#             */
/*   Updated: 2023/07/27 15:43:47 by ttofil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putnbr_chr(char *tab, int *j, long int nb)
{
	long long int	n;

	n = nb;
	if (n < 0)
	{
		n = n * -1;
		tab[*j] = '-';
		*j += 1;
	}
	if (n >= 10)
	{
		ft_putnbr_chr(tab, j, n / 10);
		ft_putnbr_chr(tab, j, n % 10);
	}
	else
	{
		tab[*j] = n + '0';
		*j += 1;
	}
}
