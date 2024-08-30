/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:10:23 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/30 11:43:55 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_list(t_linkedlist_node *head)
{
	t_linkedlist_node	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->data);
		free(temp);
	}
}

t_linkedlist_node	*copy_linked_list(t_linkedlist_node *original)
{
	t_linkedlist_node	*new_head;
	t_linkedlist_node	*current_original;
	t_linkedlist_node	*current_new;
	t_linkedlist_node	*new_node;
	
	if (original == NULL)
		return (NULL);
	new_head = create_node_l(original->data);
	if (!new_head)
		return (NULL); 
	current_original = original->next;
	current_new = new_head;
	while (current_original != NULL)
	{
		new_node = create_node_l(current_original->data);
		if (!new_node)
			return (free_list(new_head), NULL);
		current_new->next = new_node;
		current_new = new_node;
		current_original = current_original->next;
	}
	return (new_head);
}
