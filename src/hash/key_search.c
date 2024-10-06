/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:07:31 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// search the value of the key from the HASHTABLE

char	*key_search(char *key)
{
	t_hashtable	*table;
	t_hashpair	*tmp;
	int			i;

	table = g_minishell.envp;
	i = hash_function(key, table->size);
	tmp = table->list[i];
	while (tmp)
	{
		if (!ft_strncmp(tmp->hash_key, key, ft_strlen(key)))
			return (tmp->hash_value);
		tmp = tmp->next;
	}
	return (NULL);
}
