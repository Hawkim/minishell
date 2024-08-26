/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:10:23 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/22 16:30:07 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_linkedlist_node *copy_linked_list(t_linkedlist_node *original)
{
	t_linkedlist_node *new_head;
	t_linkedlist_node *current_original;
	t_linkedlist_node *current_new;
	t_linkedlist_node *new_node;
	
	if (original == NULL)
		return NULL;
	new_head = create_node_l(original->data); // Create the head of the new list
	if (!new_head)
		return NULL; 
	current_original = original->next; // Pointer for traversing the original list
	current_new = new_head; // Pointer for building the new list
	while (current_original != NULL)
	{
		new_node = create_node_l(current_original->data); // Create a new node
		if (!new_node)
		{
			t_linkedlist_node *temp;
			while (new_head != NULL)
			{
				temp = new_head;
				new_head = new_head->next;
				free(temp->data); // Free the duplicated string
				free(temp); // Free the node
			}
			return (NULL);
		}
		current_new->next = new_node; // Link the new node
		current_new = new_node; // Move to the new node
		current_original = current_original->next; // Move to the next node in the original list
	}
	return (new_head); // Return the head of the new list
}
