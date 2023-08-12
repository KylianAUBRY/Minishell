/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:06:38 by kylian            #+#    #+#             */
/*   Updated: 2023/08/12 17:13:21 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_sigle_quot(char *s1, char *str)
{
	char	*dest;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str && str[++i] && str[i] != '\'')
		;
	dest = malloc(sizeof(char) * (i + ft_strlen(s1) + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1 && s1[j])
	{
		dest[j] = s1[j];
		j++;
	}
	while (str && str[++i] && str[i] != '\'')
		dest[j + i] = str[i];
	dest[j + i] = '\0';
	if (s1)
		free(s1);
	return (dest);
}

int	ft_strlen_double_quot(char *dest, char *str, t_shell *shell)
{
	int	i;
	int	tmp;
	int	count;

	i = -1;
	count = 0;
	while (str && str[++i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			tmp = ft_strlen_chr_dol(str, i, shell);
			if (tmp == -1)
				return (-1);
			count += tmp;
			while (str[++i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' '
				&& str[i] != '\t' && str[i] != '>' && str[i] != '<'
				&& str[i] != '|')
				;
			if (!str[i] || str[i] == '\"')
				break ;
		}
		count++;
	}
	return (count + ft_strlen(dest) + 1);
}

char	*ft_cpy_tmp_to_dest(char *dest, char *tmp, int *k)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (dest[i])
		i++;
	while (tmp[++j])
	{
		dest[i + j] = tmp[j];
	}
	dest[i + j] = '\0';
	free(tmp);
	*k = (i + j);
	return (dest);
}

char	*ft_strjoin_double_quot_2(char *str, char *new_dest, int i,
		t_shell *shell)
{
	char	*tmp;
	int		j;

	j = ft_strlen(new_dest);
	while (str && str[++i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			new_dest[j] = '\0';
			tmp = ft_chr_dol(str, i, shell);
			if (!tmp)
				return (NULL);
			new_dest = ft_cpy_tmp_to_dest(new_dest, tmp, &j);
			while (str[++i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' '
				&& str[i] != '\t' && str[i] != '>' && str[i] != '<'
				&& str[i] != '|')
				;
			if (!str[i] || str[i] == '\"')
				return (new_dest);
		}
		new_dest[j] = str[i];
		j++;
	}
	new_dest[j] = '\0';
	return (new_dest);
}

char	*ft_strjoin_double_quot(char *dest, char *str, t_shell *shell)
{
	char	*new_dest;
	int		i;

	i = ft_strlen_double_quot(dest, str, shell);
	if (i == -1)
		return (NULL);
	new_dest = malloc(sizeof(char) * i + 1);
	if (!new_dest)
		return (NULL);
	i = 0;
	while (dest && dest[i])
	{
		new_dest[i] = dest[i];
		i++;
	}
	new_dest[i] = '\0';
	if (dest)
		free(dest);
	return (ft_strjoin_double_quot_2(str, new_dest, -1, shell));
}
