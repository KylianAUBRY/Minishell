/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_modif.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:15:47 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/11 14:54:38 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_modif_pipe_2(char *s1)
{
	int		i;
	char	*dest;

	i = -1;
	dest = malloc(sizeof(char) * (ft_strlen(s1) * 2));
	if (!dest)
		return (NULL);
	dest[0] = PCD;
	while (s1[++i])
		dest[i + 1] = s1[i];
	dest[i + 1] = '\0';
	free(s1);
	return (dest);
}

char	*ft_strjoin_modif_pipe(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s2)
		return (ft_strjoin_modif_pipe_2(s1));
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
