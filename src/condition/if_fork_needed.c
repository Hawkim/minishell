/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_fork_needed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:18:01 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 11:51:22 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_fork_needed(t_command *cmd, t_minishell *g_minishell)
{
	if (!ft_strncmp(cmd->exe_path, "cd\0", 3)
		|| !ft_strncmp(cmd->exe_path, "unset\0", 6)
		|| !ft_strncmp(cmd->exe_path, "exit\0", 5))
	{
		if (!cmd->is_piped)
			exe_builtin_parent(cmd, g_minishell);
		return (0);
	}
	else if (!ft_strncmp(cmd->exe_path, "export\0", 7)
		&& cmd->exe[1] && *cmd->exe[1])
	{
		if (!cmd->is_piped)
			exe_builtin_parent(cmd, g_minishell);
		return (0);
	}
	return (1);
}
