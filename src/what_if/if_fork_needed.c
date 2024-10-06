/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_fork_needed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:18:01 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/27 17:22:36 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_fork_needed(t_command *cmd)
{
	if (!ft_strncmp(cmd->exec_path, "cd\0", 3)
		|| !ft_strncmp(cmd->exec_path, "unset\0", 6)
		|| !ft_strncmp(cmd->exec_path, "exit\0", 5))
	{
		if (!cmd->is_piped)
			exec_builtin_parent(cmd);
		return (0);
	}
	else if (!ft_strncmp(cmd->exec_path, "export\0", 7)
		&& cmd->exec[1] && *cmd->exec[1])
	{
		if (!cmd->is_piped)
			exec_builtin_parent(cmd);
		return (0);
	}
	return (1);
}
