/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaekim <gaekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:56:00 by daelee            #+#    #+#             */
/*   Updated: 2021/02/08 01:39:13 by gaekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_cd_home(char *path, char **cmdline, char **envs)
{
	if (cmdline[1][1] == '~')
	{
		print_execute_err_2("cd", cmdline[1], "No such file or directory");
		g_exit_status = 1;
	}
	path = find_value("HOME", envs);
	if (chdir(path) == -1)
		print_execute_err_1("cd", "HOME not set");
	return (SUCCESS);
}

int			ft_cd_envv(char *path, char **cmdline, char **envs)
{
	path = find_value(&(cmdline[1][1]), envs);
	if (chdir(path) == -1)
		chdir(find_value("HOME", envs));
	return (SUCCESS);
}

void		set_oldpwd_pwd(char **envs)
{
	char	*cur_pwd;
	char	*old_pwd;
	char	*tmp;

	tmp = malloc(sizeof(char) * MAXSIZE);
	cur_pwd = ft_strjoin("PWD=", getcwd(tmp, MAXSIZE));
	old_pwd = ft_strjoin("OLDPWD=", find_value("PWD", envs));
	check_export(cur_pwd, &envs);
	check_export(old_pwd, &envs);
	free(cur_pwd);
	free(old_pwd);
}

void		ft_cd(char **cmdline, char **envs)
{
	char	*path;
	int		ret;

	path = 0;
	ret = 0;
	if (cmdline[1] != NULL && cmdline[1][0] != '~' && cmdline[1][0] != '$')
	{
		path = cmdline[1];
		if (chdir(path) == -1)
			ret = print_execute_err_2("cd", path, strerror(errno));
		set_oldpwd_pwd(envs);
	}
	else if (cmdline[1] == NULL || cmdline[1][0] == '~')
		ft_cd_home(path, cmdline, envs);
	else if (cmdline[1][0] == '$')
		ft_cd_envv(path, cmdline, envs);
	if (ret == ERROR)
		g_exit_status = 1;
	else
		g_exit_status = 0;
}
