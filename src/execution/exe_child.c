/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:43:08 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 13:20:29 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_all_fds(t_minishell *g_minishell)
{
	t_command	*cmd;

	cmd = g_minishell->command;
	while (cmd)
	{
		close_fd(cmd, BOTH);
		cmd = cmd->next;
	}
}

void	exe_child(t_command *cmd, t_minishell *g_minishell)
{
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	close_all_fds(g_minishell);
	if (if_builtin(cmd))
		exe_builtin_child(cmd, g_minishell);
	else
	{
		exe_commands_child_signals();
		execve(cmd->exe_path, cmd->exe, cmd->envp);
		return_error(cmd->exe[0], errno, g_minishell);
	}
	free_shell(g_minishell);
	exit(g_minishell->exit_code);
}
