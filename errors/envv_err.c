/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 01:33:33 by daelee            #+#    #+#             */
/*   Updated: 2021/02/08 01:39:13 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_identifier_err(char *token1, char *token2)
{
	ft_putstr_fd("minishell", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(token1, STDERR);
	ft_putstr_fd(": `", STDERR);
	ft_putstr_fd(token2, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
}
