/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:15:29 by kylian            #+#    #+#             */
/*   Updated: 2023/08/12 13:18:35 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_error_malloc(char **dest)
{
	int	i;

	i = -1;
	while (dest[++i])
		free(dest[i]);
	free(dest);
	return (NULL);
}

int	fill_tab_pr(char **dest, char *str, int i)
{
	int	j;

	j = 0;
	while (dest[j])
		j++;
	if (str[i] == '|' || (str[i] == '>' && str[i + 1] != '>') || (str[i] == '<'
			&& str[i + 1] != '>' && str[i + 1] != '<'))
		dest[j] = malloc(sizeof(char) * 3);
	else
		dest[j] = malloc(sizeof(char) * 4);
	if (!dest)
		return (print_error_message(ERRCODE_MALLOC));
	dest[j][0] = PR;
	dest[j][1] = str[i];
	if (str[i] == '|' || (str[i] == '>' && str[i + 1] != '>') || (str[i] == '<'
			&& str[i + 1] != '>' && str[i + 1] != '<'))
	{
		dest[j][2] = '\0';
		dest[j + 1] = NULL;
		return (0);
	}
	dest[j][2] = str[i + 1];
	dest[j][3] = '\0';
	dest[j + 1] = NULL;
	return (0);
}

int	ft_chr_cmd_or_arg(char **dest)
{
	int	j;

	j = 0;
	while (dest[j])
		j++;
	if (j == 0)
		return (IS_CMD);
	if (dest[j - 1][0] == PR && dest[j - 1][1] != '|')
		return (IS_ARG);
	else if (dest[j - 1][0] == PR && dest[j - 1][1] == '|')
		return (IS_CMD);
	while (--j >= 0)
	{
		if (dest[j][0] == CMD || dest[j][0] == ERR || dest[j][0] == CMDCUSTOM)
			return (IS_ARG);
		if (dest[j][0] == PR && dest[j][1] == '|')
			return (IS_CMD);
	}
	return (IS_CMD);
}

char	**ft_fill_parsing_tab(char **dest, char *str, int i, t_shell *shell)
{
	while (str && str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
		{
			if (fill_tab_pr(dest, str, i) == 1)
				return (ft_error_malloc(dest));
			i = ft_skeep_redir(str, i);
		}
		else if (str[i])
		{
			if (ft_chr_cmd_or_arg(dest) == IS_CMD)
			{
				if (ft_fill_tab_cmd(dest, str, i, shell) == 1)
					return (ft_error_malloc(dest));
			}
			else if (ft_fill_tab_arg(dest, str, i, shell) == 1)
				return (ft_error_malloc(dest));
			i = ft_skeep_word(str, i);
		}
	}
	return (dest);
}
