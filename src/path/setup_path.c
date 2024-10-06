/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:06:27 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/27 17:18:25 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// split a path into a list of directions
//int access(const char *pathname, int mode)

//  access() checks whether the calling process can access the file pathname
//X_OK	1		/* Test for execute permission.  */
//F_OK	0		/* Test for existence.  */
//  cleans the previous path and search for the new one
//  if not in builtin -> searched in the PATH env variable
// split by ':'
// If the command is found, the path is returned
// return to a string (path to the cmd)
char	*setup_path(t_command *cmd)
{
	char	**path_list;
	char	*path;
	char	*tmp;

	path_list = NULL;
	path = NULL;
	if (ft_strchr(cmd->exec[0], '/') != NULL)
	{
		path = ft_strdup(cmd->exec[0]);
		return (path);
	}
	tmp = key_search("PATH");
	if (tmp)
		path_list = ft_split(tmp, ':');
	if (path_list)
		check_path(cmd, path_list, &path);
	if (!path && !access(cmd->exec[0], F_OK | X_OK))
		path = ft_strdup(cmd->exec[0]);
	return (path);
}
