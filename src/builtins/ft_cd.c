/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:18:39 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/27 17:10:08 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//  change the value of the PWD and OLDPWD after cd is executed

char	**create_export(char *pwd, char *oldpwd)
{
	char	**exec;
	char	*cmd;

	exec = ft_calloc(4, sizeof(char *));
	if (!exec)
		return (NULL);
	cmd = ft_strdup("export");
	exec[0] = cmd;
	exec[1] = pwd;
	exec[2] = oldpwd;
	return (exec);
}

int	change_cd(char *path)
{
	char	*oldpwd;
	char	*pwd;
	char	*curr_pwd;
	char	**exec;

	if (chdir(path) == -1)
	{
		if (errno == ENOTDIR)
			print_error("cd: ", path, ": Not a directory.");
		else
			print_error("cd: ", path, ": No such file or directory.");
		g_minishell.exit_code = 1;
		return (1);
	}
	oldpwd = ft_strjoin("OLDPWD=", key_search("PWD"));
	curr_pwd = getcwd(NULL, 0);
	pwd = ft_strjoin ("PWD=", curr_pwd);
	free(curr_pwd);
	exec = create_export(pwd, oldpwd);
	ft_export(exec);
	free_export(exec);
	return (0);
}

int	cd_path(char *variable)
{
	char	*path;
	int		result;

	path = key_search(variable);
	result = 1;
	if (!path || !*path)
	{
		print_error("cd: `", variable, "\': is not set.");
		g_minishell.exit_code = 1;
	}
	else
	{
		if (!ft_strncmp ("OLDPWD", variable, 6))
			printf("%s\n", path);
		result = change_cd (path);
	}
	return (result);
}

// handles the cd builtin with
// no args -> cd to home
// correct args -> cd to dest dir
// more args ->error

int	check_valid_option(char *exec)
{
	int	len;

	len = ft_strlen(exec);
	if (exec[0] == '-' && len > 1)
	{
		print_error("cd: `", exec, "\': invalid option.");
		return (1);
	}
	return (0);
}

int	ft_cd(char **exec)
{
	char	*param;
	int		result;

	param = exec[1];
	result = 1;
	if (param && exec[2])
	{
		print_error("cd:", NULL, " too many arguments.");
		return (1);
	}
	else if (param && check_valid_option(param))
		return (2);
	else if (!param || !*param || !ft_strncmp(param, "~\0", 2)
		|| !ft_strncmp(param, "#\0", 2))
		result = cd_path("HOME");
	else if (!ft_strncmp(param, "-", 2))
		result = cd_path("OLDPWD");
	else
		result = change_cd(param);
	return (result);
}
