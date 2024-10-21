/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:43:48 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 13:31:51 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//exit :  exit the shell as a whole
//cd & unset update the environment 
//variables in both child & parent
void	exe_builtin_parent(t_command *cmd)
{
	if (!ft_strncmp (cmd->exe_path, "cd\0", 3))
		g_minishell.exit_code = ft_cd(cmd->exe);
	else if (!ft_strncmp (cmd->exe_path, "export\0", 7))
		g_minishell.exit_code = ft_export(cmd->exe);
	else if (!ft_strncmp (cmd->exe_path, "unset\0", 6))
		g_minishell.exit_code = ft_unset(cmd->exe);
	else if (!ft_strncmp (cmd->exe_path, "exit\0", 5))
		g_minishell.exit_code = ft_exit(cmd->exe);
	free_envp(cmd);
	create_exe_envp(cmd);
}

void	exe_builtin_child(t_command *cmd)
{
	if (!ft_strncmp (cmd->exe_path, "env\0", 4))
		g_minishell.exit_code = ft_env(cmd);
	else if (!ft_strncmp (cmd->exe_path, "export\0", 7))
		g_minishell.exit_code = ft_export(cmd->exe);
	else if (!ft_strncmp (cmd->exe_path, "echo\0", 5))
		g_minishell.exit_code = ft_echo(cmd->exe);
	else if (!ft_strncmp (cmd->exe_path, "pwd\0", 4))
		g_minishell.exit_code = ft_pwd(cmd->exe);
}
