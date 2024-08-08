/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:56:01 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/08 11:48:22 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	int		i;
	int		size;

	size = 0;
	while (src[size])
		size++;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

// Function to create a new linked list node
t_linkedlist_node *create_node(char *data) {
    t_linkedlist_node *new_node = malloc(sizeof(t_linkedlist_node));
    if (!new_node) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    new_node->data = strdup(data); // Copy the data
    new_node->next = NULL;
    return new_node;
}

// Function to append a new node to the end of the linked list
void append(t_linkedlist_node **list, char *data) {
    t_linkedlist_node *new_node = create_node(data);
    if (*list == NULL) {
        *list = new_node;
    } else {
        t_linkedlist_node *current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to print all tokens in the linked list
void print_tokens(t_linkedlist_node *list) {
    t_linkedlist_node *current = list;
    while (current != NULL) {
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
