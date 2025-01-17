/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyy_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:07:31 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 11:51:22 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// search the value of the keyy from the HASHTABLE

char	*keyy_search(char *keyy, t_minishell *g_minishell)
{
	t_hashtable	*table;
	t_hashpair	*tmp;
	int			i;

	table = g_minishell->envp;
	i = hash_function(keyy, table->size);
	tmp = table->list[i];
	while (tmp)
	{
		if (!ft_strncmp(tmp->hash_keyy, keyy, ft_strlen(keyy)))
			return (tmp->hash_value);
		tmp = tmp->next;
	}
	return (NULL);
}
