/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:06:36 by ttofil            #+#    #+#             */
/*   Updated: 2023/07/13 16:29:44 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_2d_array2(char **tab, int j)
{
	while (j > 0)
		free(tab[j--]);
	free(tab);
}

static int	len_word2(const char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

static char	*get_word2(const char *str, int *i, char sep)
{
	int		j;
	int		c_letter;
	char	*tab;

	j = 0;
	c_letter = len_word2(str + *i, sep);
	tab = malloc(sizeof(char) * (c_letter + 1));
	if (tab == NULL)
		return (NULL);
	while (j < c_letter)
	{
		tab[j++] = str[*i];
		*i += 1;
	}
	tab[j] = 0;
	return (tab);
}

static int	count_words2(const char *str, char sep)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] && str[i] == sep)
		i++;
	while (str[i])
	{
		while (str[i] && str[i] != sep)
			i++;
		len++;
		while (str[i] && str[i] == sep)
			i++;
	}
	return (len);
}

char	**ft_split(const char *str, char sep)
{
	int		i;
	int		j;
	int		c_word;
	char	**tab;

	i = 0;
	j = 0;
	c_word = count_words2(str, sep);
	tab = malloc(sizeof(char *) * (c_word + 1));
	if (tab == NULL)
		return (NULL);
	while (j < c_word)
	{
		while (str[i] && str[i] == sep)
			i++;
		tab[j] = get_word2(str, &i, sep);
		if (tab[j] == NULL)
		{
			free_2d_array2(tab, j);
			return (NULL);
		}
		j++;
	}
	tab[j] = 0;
	return (tab);
}
