/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrch_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:57:06 by kylian            #+#    #+#             */
/*   Updated: 2023/08/12 13:41:20 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_modif_word(char *s1, char *str)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str && str[i] && ft_chr_char(str[i]) == 0)
		i++;
	dest = malloc(sizeof(char) * (ft_strlen(s1) + i + 2));
	if (dest)
	{
		i = -1;
		while (s1 && s1[j])
		{
			dest[j] = s1[j];
			j++;
		}
		while (str && str[++i] && ft_chr_char(str[i]) == 0)
			dest[j + i] = str[i];
		dest[j + i] = '\0';
	}
	if (s1)
		free(s1);
	return (dest);
}

int	ft_chr_i_word(char *str, int i)
{
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '>'
		&& str[i] != '<' && str[i] != '|' && str[i] != '\'' && str[i] != '\"'
		&& str[i] != '$')
		i++;
	return (i);
}

char	*ft_chr_other(char *str, int i, t_shell *shell, char *dest)
{
	if (str[i] == '$')
	{
		if (str[i + 1] == '?')
			dest = ft_strjoin_4(dest, ft_itoa(shell->var_global.res));
		else
			dest = ft_strjoin_4(dest, ft_chr_dol(str, i, shell));
		if (!dest)
			return (NULL);
	}
	else if (str[i] == '\'')
	{
		dest = ft_strjoin_sigle_quot(dest, str + (i + 1));
		if (!dest)
			return (NULL);
	}
	else if (str[i] == '\"')
	{
		dest = ft_strjoin_double_quot(dest, str + (i + 1), shell);
		if (!dest)
			return (NULL);
	}
	return (dest);
}

int	ft_chr_i_other(char *str, int i)
{
	if (str[i] == '$')
	{
		while (str[++i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' '
			&& str[i] != '\t' && str[i] != '>' && str[i] != '<'
			&& str[i] != '|')
			;
	}
	else if (str[i] == '\'')
	{
		while (str && str[++i] && str[i] != '\'')
			;
		i++;
	}
	else if (str[i] == '\"')
	{
		while (str && str[++i] && str[i] != '\"')
			;
		i++;
	}
	return (i);
}

char	*ft_chrch_name(char *str, int i, t_shell *shell)
{
	char	*dest;

	dest = NULL;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '>'
		&& str[i] != '<' && str[i] != '|')
	{
		if (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != '$')
		{
			dest = ft_strjoin_modif_word(dest, str + i);
			if (!dest)
				return (NULL);
			i = ft_chr_i_word(str, i);
		}
		else if (str[i] && (str[i] == '$' || str[i] == '\'' || str[i] == '\"'))
		{
			dest = ft_chr_other(str, i, shell, dest);
			if (!dest)
				return (NULL);
			i = ft_chr_i_other(str, i);
		}
	}
	return (dest);
}
