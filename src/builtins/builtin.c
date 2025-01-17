/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:43:48 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 13:15:56 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//exit :  exit the shell as a whole
//cd & unset update the environment 
//variables in both child & parent
void	exe_builtin_parent(t_command *cmd, t_minishell *g_minishell)
{
	if (!ft_strncmp (cmd->exe_path, "cd\0", 3))
		g_minishell->exit_code = ft_cd(cmd->exe, g_minishell);
	else if (!ft_strncmp (cmd->exe_path, "export\0", 7))
		g_minishell->exit_code = ft_export(cmd->exe, g_minishell);
	else if (!ft_strncmp (cmd->exe_path, "unset\0", 6))
		g_minishell->exit_code = ft_unset(cmd->exe, g_minishell);
	else if (!ft_strncmp (cmd->exe_path, "exit\0", 5))
		g_minishell->exit_code = ft_exit(cmd->exe, g_minishell);
	free_envp(cmd);
	create_exe_envp(cmd, g_minishell);
}

void	exe_builtin_child(t_command *cmd, t_minishell *g_minishell)
{
	if (!ft_strncmp (cmd->exe_path, "env\0", 4))
		g_minishell->exit_code = ft_env(cmd, g_minishell);
	else if (!ft_strncmp (cmd->exe_path, "export\0", 7))
		g_minishell->exit_code = ft_export(cmd->exe, g_minishell);
	else if (!ft_strncmp (cmd->exe_path, "echo\0", 5))
		g_minishell->exit_code = ft_echo(cmd->exe);
	else if (!ft_strncmp (cmd->exe_path, "pwd\0", 4))
		g_minishell->exit_code = ft_pwd(cmd->exe, g_minishell);
}
