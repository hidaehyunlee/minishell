/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <daelee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:59:48 by daelee            #+#    #+#             */
/*   Updated: 2021/01/14 14:08:36 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo(char **cmdline)
{
	int		i;
	int		option;

	i = 0;
	option = 0;
	while (cmdline[++i])
	{
		while (cmdline[i] && (option + 1) == i &&
		!ft_strncmp(cmdline[i], "-n", ft_strlen(cmdline[i])))
		{
			if (cmdline[i + 1] == NULL)
				return ;
			option++;
			i++;
		}
		ft_putstr_fd(cmdline[i], 1);
		if (cmdline[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
}