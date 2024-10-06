/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:53:12 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/27 17:21:23 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_folder_path(void)
{
	char	*path;
	char	*folder;
	char	*folder_path;

	path = get_pwd();
	folder = ft_strrchr (path, '/');
	folder_path = ft_strjoin(&folder[1], "/");
	free(path);
	return (folder_path);
}
