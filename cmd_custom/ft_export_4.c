/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:09:55 by kyaubry           #+#    #+#             */
/*   Updated: 2023/07/28 00:35:11 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_free_line_export(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (print_error_message(ERRCODE_MALLOC));
}

char	*ft_strdup_join(const char *s, char *src2)
{
	char	*dest;
	int		i;
	int		j;

	dest = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(src2) + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	if (!src2)
		return (dest);
	dest[i] = '=';
	j = -1;
	i++;
	while (src2[++j] != '\0')
		dest[i + j] = src2[j];
	dest[i + j] = '\0';
	return (dest);
}

void	ft_swap_val(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
