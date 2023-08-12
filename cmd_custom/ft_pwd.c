/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyaubry <kyaubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:15:42 by kyaubry           #+#    #+#             */
/*   Updated: 2023/08/10 16:33:47 by kyaubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	chemin[4096];

	if (getcwd(chemin, 4096) != NULL)
		printf("%s\n", chemin);
	else
		return (print_error_message(ERRCODE_GETCWD));
	return (0);
}
