/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:29:44 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 11:51:22 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**create_path_list(t_minishell *g_minishell)
{
	char	**path;
	char	*temp;

	path = NULL;
	temp = keyy_search("PATH", g_minishell);
	if (temp)
		path = ft_split (temp, ':');
	return (path);
}
