/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_dol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:14:12 by kylian            #+#    #+#             */
/*   Updated: 2023/08/12 12:55:26 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_chr_global_var(char *name, t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->var_global.tab[++i])
		if (ft_strcmp(shell->var_global.tab[i][0], name) == 0)
			return (shell->var_global.tab[i][1]);
	return ("");
}

char	*ft_chr_dol(char *str, int i, t_shell *shell)
{
	char	*name;
	char	*dest;
	int		j;
	int		tmp;

	tmp = i;
	j = 0;
	if (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0')
		return (ft_strdup("$"));
	while (str[++i] && ft_chr_char_2(str[i]) == 0)
		j++;
	name = malloc(sizeof(char) * (j + 1));
	if (!name)
		return (NULL);
	i = tmp;
	j = -1;
	while (str[++i] && ft_chr_char_2(str[i]) == 0)
		name[++j] = str[i];
	name[++j] = '\0';
	dest = ft_strdup(ft_chr_global_var(name, shell));
	if (!dest)
		print_error_message(ERRCODE_MALLOC);
	free(name);
	return (dest);
}

int	ft_strlen_chr_dol(char *str, int i, t_shell *shell)
{
	char	*name;
	int		dest;
	int		j;
	int		tmp;

	tmp = i;
	j = 0;
	while (str[++i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' '
		&& str[i] != '\t' && str[i] != '>' && str[i] != '<' && str[i] != '|')
		j++;
	name = malloc(sizeof(char) * (j + 1));
	if (!name)
		return (-1);
	i = tmp;
	j = -1;
	while (str[++i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' '
		&& str[i] != '\t' && str[i] != '>' && str[i] != '<' && str[i] != '|')
		name[++j] = str[i];
	name[++j] = '\0';
	dest = ft_strlen(ft_chr_global_var(name, shell));
	free(name);
	if (dest == 0)
		return (1);
	return (dest);
}
