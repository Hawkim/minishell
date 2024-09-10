/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:56:01 by jabanna           #+#    #+#             */
/*   Updated: 2024/09/10 11:12:09 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_linkedlist_node	*create_node_l(char *data)
{
	t_linkedlist_node	*new_node;

	new_node = malloc(sizeof(t_linkedlist_node));
	if (!new_node)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	new_node->data = ft_strdup(data);
	new_node->next = NULL;
	return (new_node);
}

void	append(t_linkedlist_node **list, char *data)
{
	t_linkedlist_node	*new_node;
	t_linkedlist_node	*current;

	new_node = create_node_l(data);
	if (*list == NULL)
		*list = new_node;
	else
	{
		current = *list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

// Function to print all tokens in the linked list
void	print_tokens(t_linkedlist_node *list)
{
	t_linkedlist_node	*current;

	current = list;
	while (current != NULL)
	{
		printf("Token: %s\n", current->data);
		current = current->next;
	}
}

// void	append(t_linkedlist_node **token_list, char *s)
// {
// 	t_linkedlist_node	*new_token;
// 	t_linkedlist_node	*current;

// 	if (s == NULL)
// 		return ;
// 	new_token = malloc(sizeof(t_linkedlist_node));
// 	if (!new_token)
// 		return ;
// 	new_token->data = ft_strdup(s);
// 	if (new_token->data == NULL)
// 	{
// 		free(new_token);
// 		return ;
// 	}
// 	new_token->next = NULL;
// 	if (*token_list == NULL)
// 		*token_list = new_token;
// 	else
// 	{
// 		current = *token_list;
// 		while (current->next != NULL)
// 			current = current->next;
// 		current->next = new_token;
// 	}
// }
