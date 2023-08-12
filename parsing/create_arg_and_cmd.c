/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arg_and_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 01:45:45 by kylian            #+#    #+#             */
/*   Updated: 2023/08/11 16:52:55 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_fill_tab_arg(char **dest, char *str, int i, t_shell *shell)
{
	int		j;
	char	*name;

	j = -1;
	while (dest[++j])
		;
	name = ft_chrch_name(str, i, shell);
	if (!name)
		return (print_error_message(ERRCODE_MALLOC));
	dest[j] = ft_strdup_char(name, ARG);
	free(name);
	if (!dest[j])
		return (print_error_message(ERRCODE_MALLOC));
	dest[j + 1] = NULL;
	return (0);
}

int	ft_chr_cmd_custom(char *name)
{
	if (ft_strcmp(name, "echo") == 0 || ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0 || ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0 || ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

char	*get_command_2(char *name, t_shell *shell)
{
	int		i;
	char	*cmd;
	char	**paths;

	i = -1;
	if (access(name, F_OK | X_OK) == 0)
		return (ft_strdup(name));
	paths = get_path(shell);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		cmd = ft_strjoin_paths_cmd(paths[i], name);
		if (!cmd || access(cmd, F_OK | X_OK) == 0)
		{
			ft_free_cmd(paths);
			return (cmd);
		}
		free(cmd);
	}
	ft_free_cmd(paths);
	return (NULL);
}

int	get_command(char **name, t_shell *shell)
{
	char	*cmd;

	cmd = get_command_2(*name, shell);
	if (!cmd)
		return (0);
	free(*name);
	*name = cmd;
	return (1);
}

int	ft_fill_tab_cmd(char **dest, char *str, int i, t_shell *shell)
{
	int		j;
	char	*name;

	j = -1;
	while (dest[++j])
		;
	name = ft_chrch_name(str, i, shell);
	if (!name)
		return (print_error_message(ERRCODE_MALLOC));
	if (ft_chr_cmd_custom(name) == 1)
		dest[j] = ft_strdup_char(name, CMDCUSTOM);
	else if (get_command(&name, shell) == 1)
		dest[j] = ft_strdup_char(name, CMD);
	else
		dest[j] = ft_strdup_char(name, ERR);
	free(name);
	if (!dest[j])
		return (print_error_message(ERRCODE_MALLOC));
	dest[j + 1] = NULL;
	return (0);
}
