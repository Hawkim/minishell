/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:28:09 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 12:54:10 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_cmd_path(t_command *cmd, t_minishell *g_minishell)
{
	char		*path;

	if (!*cmd->exe)
		return (NULL);
	if (cmd->exe_path)
		free(cmd->exe_path);
	if (if_builtin(cmd))
		path = ft_strdup(cmd->exe[0]);
	else
	{
		path = setup_path(cmd, g_minishell);
		if (!path)
		{
			if (!keyy_search("PATH", g_minishell))
				cmd_error(cmd, 1, g_minishell);
			else
				cmd_error(cmd, 2, g_minishell);
		}
	}
	return (path);
}
