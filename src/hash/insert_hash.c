/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:15:59 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Inserts a new variable at the end of the hashtable's correct hashlist

void	insert_hash(char *key, char *value, int attribute)
{
	t_hashtable	*table;
	int			i;

	table = g_minishell.envp;
	i = hash_function(key, table->size);
	bk_hash(&(table->list[i]), key, value, attribute);
	table->count++;
	free(key);
	free(value);
}
