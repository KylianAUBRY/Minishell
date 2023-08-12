/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:05:24 by kylian            #+#    #+#             */
/*   Updated: 2023/08/12 13:45:54 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kylian <kylian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:05:24 by kylian            #+#    #+#             */
/*   Updated: 2023/08/01 01:46:24 by kylian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_skeep_word(char *str, int i)
{
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '>'
		&& str[i] != '<' && str[i] != '|')
	{
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == '\"')
			while (str[++i] && str[i] != '\"')
				;
		i++;
	}
	return (i);
}

int	ft_skeep_redir(char *str, int i)
{
	if (str[i] == '<')
	{
		i++;
		if (str[i] == '<' || str[i] == '>')
			i++;
	}
	else if (str[i] == '>')
	{
		i++;
		if (str[i] == '>')
			i++;
	}
	else if (str[i] == '|')
		i++;
	return (i);
}

int	ft_count_word(char *str)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		j = i;
		i = ft_skeep_word(str, i);
		if (i != j)
			count++;
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		j = i;
		i = ft_skeep_redir(str, i);
		if (i != j)
			count++;
	}
	return (count);
}

char	**split_master(char *str, t_shell *shell)
{
	char	**dest;
	int		i;

	if (!str || !str[0] || ft_verif_syntax(str, 0) == 1)
		return (NULL);
	i = ft_count_word(str);
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
	{
		print_error_message(ERRCODE_MALLOC);
		return (NULL);
	}
	dest[0] = NULL;
	return (ft_fill_parsing_tab(dest, str, 0, shell));
}
