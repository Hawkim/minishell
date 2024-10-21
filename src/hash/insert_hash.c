/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:15:59 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 14:10:29 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Inserts a new variable at the end of the hashtable's correct hashlist

void	insert_hash(char *keyy, char *value, int attribute)
{
	t_hashtable	*table;
	int			i;

	table = g_minishell.envp;
	i = hash_function(keyy, table->size);
	bk_hash(&(table->list[i]), keyy, value, attribute);
	table->count++;
	free(keyy);
	free(value);
}
