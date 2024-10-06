/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:28:09 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_cmd_path(t_command *cmd)
{
	char		*path;

	if (!*cmd->exec)
		return (NULL);
	if (cmd->exec_path)
		free(cmd->exec_path);
	if (if_builtin(cmd))
		path = ft_strdup(cmd->exec[0]);
	else
	{
		path = setup_path(cmd);
		if (!path)
		{
			if (!key_search("PATH"))
				cmd_error(cmd, 1);
			else
				cmd_error(cmd, 2);
		}
	}
	return (path);
}
