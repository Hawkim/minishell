/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:43:08 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/01 18:33:02 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_all_fds(void)
{
	t_command	*cmd;

	cmd = g_minishell.command;
	while (cmd)
	{
		close_fd(cmd, BOTH);
		cmd = cmd->next;
	}
}

void	exec_child(t_command *cmd)
{
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	close_all_fds();
	if (if_builtin(cmd))
		exec_builtin_child(cmd);
	else
	{
		exec_commands_child_signals();
		execve(cmd->exec_path, cmd->exec, cmd->envp);
		return_error(cmd->exec[0], errno);
	}
	free_minishell();
	exit(g_minishell.exit_code);
}
