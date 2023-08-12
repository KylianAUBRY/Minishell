/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:09:11 by kylian            #+#    #+#             */
/*   Updated: 2023/08/11 16:37:55 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pass_space(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int	ft_chr_char(char c)
{
	if (c != ' ' && c != '\t' && c != '>' && c != '<' && c != '|' && c != '\''
		&& c != '\"' && c != '$')
		return (0);
	return (1);
}

int	ft_chr_char_2(char c)
{
	if (c != ' ' && c != '\t' && c != '>' && c != '<' && c != '|' && c != '\''
		&& c != '\"')
		return (0);
	return (1);
}

char	**get_path(t_shell *shell)
{
	int		i;
	char	**dest;

	i = 0;
	while (shell->var_global.tab[i] && ft_strcmp(shell->var_global.tab[i][0],
		"PATH") != 0)
		i++;
	if (!shell->var_global.tab[i])
		return (NULL);
	dest = ft_split(shell->var_global.tab[i][1], ':');
	if (!dest)
	{
		print_error_message(ERRCODE_MALLOC);
		return (NULL);
	}
	return (dest);
}

char	*ft_strjoin_paths_cmd(char *paths, char *name)
{
	int		i;
	int		j;
	char	*dest;

	i = -1;
	j = -1;
	dest = malloc(sizeof(char) * ft_strlen(paths) + ft_strlen(name) + 2);
	if (!dest)
	{
		print_error_message(ERRCODE_MALLOC);
		return (NULL);
	}
	while (paths && paths[++i])
		dest[i] = paths[i];
	dest[i] = '/';
	i++;
	while (name && name[++j])
		dest[i + j] = name[j];
	dest[i + j] = '\0';
	return (dest);
}
