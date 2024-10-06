/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:13:46 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//adds a new pair to the end of the list

void	bk_hash(t_hashpair **list, char *key, char *value, int atr)
{
	t_hashpair	*new;
	t_hashpair	*tmp;

	new = malloc (sizeof(t_hashpair));
	if (!new)
		return ;
	new->hash_key = ft_strdup(key);
	new->hash_value = ft_strdup(value);
	new->attribute = atr;
	new->next = NULL;
	tmp = *list;
	if (!tmp)
		*list = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
