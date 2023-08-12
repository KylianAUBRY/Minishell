/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:09:28 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/12 12:52:34 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_3(char **args, char **cmd, t_shell *shell)
{
	shell->var_global.res_tmp = 0;
	if (args && args[1])
		shell->var_global.res_tmp = ft_atoi(args[1]);
	if (shell->var_global.res_tmp > 255)
		shell->var_global.res_tmp = 255;
	if (shell->var_global.res_tmp < -255)
		shell->var_global.res_tmp = -255;
	return (ft_free_error_exec(cmd, shell, args));
}

int	ft_exit_2(char **args, char **cmd, t_shell *shell)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	while (args && args[1] && (args[1][i] == ' ' || args[1][i] == ' '))
		i++;
	if (args[1][i] == '-')
	{
		i++;
		neg++;
	}
	while (args && args[1] && args[1][i] == '0')
		i++;
	if (ft_strlen(args[1] + i) > 4)
	{
		shell->var_global.res_tmp = 255;
		if (neg == 1)
			shell->var_global.res_tmp = -255;
		return (ft_free_error_exec(cmd, shell, args));
	}
	return (ft_exit_3(args, cmd, shell));
}

int	ft_exit(char **args, char **cmd, t_shell *shell)
{
	int	i;

	i = 0;
	shell->var_global.res_tmp = 0;
	if (args && !args[1])
		return (ft_free_error_exec(cmd, shell, args));
	while (args && args[1] && (args[1][i] == ' ' || args[1][i] == ' '))
		i++;
	if (args[1][i] == '-')
		i++;
	while (args && args[1] && args[1][i] >= '0' && args[1][i] <= '9')
		i++;
	if (args && args[1] && args[1][i] != '\0')
	{
		ft_print_error_custom("minishell: exit: numeric argument required\n");
		shell->var_global.res_tmp = 2;
		return (ft_free_error_exec(cmd, shell, args));
	}
	if (args && args[1] && args[2])
	{
		ft_print_error_custom("minishell: exit: too many arguments\n");
		return (1);
	}
	return (ft_exit_2(args, cmd, shell));
}
