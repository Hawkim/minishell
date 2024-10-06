/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:28:54 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Check if a file exists and is executable
void	check_path(t_command *cmd, char **path_list, char **path)
{
	char	*curr_path;
	int		i;

	i = -1;
	while (path_list[++i])
	{
		curr_path = ft_strnjoin (3, path_list[i], "/", cmd->exec[0]);
		if (access(curr_path, F_OK) == 0)
		{
			*path = curr_path;
			break ;
		}
		free(curr_path);
	}
	free_path(path_list);
}
