/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:28:09 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 14:10:29 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_cmd_path(t_command *cmd)
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
		path = setup_path(cmd);
		if (!path)
		{
			if (!keyy_search("PATH"))
				cmd_error(cmd, 1);
			else
				cmd_error(cmd, 2);
		}
	}
	return (path);
}
