/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 00:29:34 by kyaubry           #+#    #+#             */
/*   Updated: 2023/07/31 20:50:02 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == NULL)
	{
		free(s1);
		return (NULL);
	}
	while (s1 && s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	if (i)
		free(s1);
	while (s2 && s2[j])
		dst[i++] = s2[j++];
	dst[i] = 0;
	return (dst);
}
