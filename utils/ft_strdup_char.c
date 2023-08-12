/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:08:13 by kylian            #+#    #+#             */
/*   Updated: 2023/08/01 16:27:46 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_char(const char *s, char c)
{
	char	*dest;
	int		i;

	i = ft_strlen(s);
	dest = malloc(sizeof(char) * i + 2);
	if (!dest)
		return (NULL);
	i = 0;
	dest[0] = c;
	while (s && s[i] != '\0')
	{
		dest[i + 1] = s[i];
		i++;
	}
	dest[i + 1] = '\0';
	return (dest);
}
