/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:38:47 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/28 17:33:57 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// TreeNode	*search_in_tokens(t_linkedlist_node *current)
// {
// 	// t_linkedlist_node	*current;
// 	char				*left_child_val;
// 	TreeNode			*root;
// 	char				*command;
// 	TreeNode			*firstnode;
// 	TreeNode			*secondnode;

// 	// current = token_list;
// 	root = NULL;
// 	command = strdup(" ");
// 	while (current != NULL && strcmp(current->data, "|") != 0)
// 	{
// 		command = ft_strjoin(command, current->data);
// 		if (strcmp(current->next->data, "|" ) != 0 && current->next != NULL)
// 			command = ft_strjoin(command, " ");
// 		current = current->next;
// 	}
// 	if (command != NULL)
// 		firstnode = create_node(command);
// 	command = NULL;
// 	// if (strcmp(current->data, "|") == 0)
// 	if (current != NULL && current->data != NULL)
// 	{
// 		root = create_node(current->data);
// 		firstnode->parent = root;
// 		root->left = firstnode;
// 		root->right = search_in_tokens(current->next);
// 		// return (search_in_tokens(current));
// 	}
	
// 	// root->left = create_lchild(root, command);
// 	// root->right = create_rchild(root, "RIGHTT");
// 	// root->right = search_in_tokens(token_list);
// 	return (root);
// }

// TreeNode	*create_binary_tree(t_linkedlist_node *current)
// {
// 	TreeNode	*root ;
// 	TreeNode	*firstnode ;
// 	char		*command ;
// 	char		*temp ;

// 	root= NULL;
// 	firstnode = NULL;
// 	command = ft_strdup("");
// 	temp = NULL;
// 	// Concatenate tokens before the first '|'
// 	while (current != NULL && ft_strncmp(current->data, "|", 1) != 0)
// 	{
// 		temp = ft_strjoin(command, current->data);
// 		free(command);
// 		command = temp;
// 		if (current->next != NULL && ft_strncmp(current->next->data, "|", 1) != 0)
// 		{
// 			temp = ft_strjoin(command, " ");
// 			free(command);
// 			command = temp;
// 		}
// 		current = current->next;
// 	}
// 	if (command != NULL && ft_strlen(command) > 0)
// 	{
// 		firstnode = create_node(command);
// 		free(command);  // Free the command after creating the node
// 	}
// 	// If current is not NULL and points to a '|', create a root node
// 	if (current != NULL && current->data != NULL && ft_strncmp(current->data, "|", 1) == 0)
// 	{
// 		root = create_node(current->data);
// 		// Create the left child with tokens before the first '|'
// 		root->left = firstnode;
// 		if (firstnode != NULL)
// 			firstnode->parent = root;
// 		root->right = create_binary_tree(current->next);
// 	}
// 	else if (firstnode != NULL)
// 		root = firstnode;// If no more pipes, this is a leaf node
// 	return (root);
// }

void remove_lt_and_next(t_linkedlist_node **token_list)
{
	t_linkedlist_node *current = *token_list;
	t_linkedlist_node *prev = NULL;

	// Traverse the list
	while (current != NULL)
	{
		// Check if the current node is '<' or '>'
		if (ft_strncmp(current->data, "<", 1) == 0 || ft_strncmp(current->data, ">", 1) == 0)
		{
			// Remove the current node
			t_linkedlist_node *node_to_remove = current;
			if (prev == NULL)
			{
				// We're at the head of the list
				*token_list = current->next;
			}
			else
			{
				// Bypass the current node
				prev->next = current->next;
			}

			// Free the current node's data and the node itself
			free(node_to_remove->data);
			free(node_to_remove);

			// Move to the next node
			current = prev ? prev->next : *token_list;

			// Check if there's a next node to remove
			if (current != NULL)
			{
				// Remove the next node
				t_linkedlist_node *next_node = current;
				if (prev == NULL)
				{
					// We're at the head of the list
					*token_list = current->next;
				}
				else
				{
					// Bypass the next node
					prev->next = current->next;
				}

				// Free the next node's data and the node itself
				free(next_node->data);
				free(next_node);

				// Move to the next node after the one we just removed
				current = prev ? prev->next : *token_list;
			}
		}
		else
		{
			// Move to the next node
			prev = current;
			current = current->next;
		}
	}
}


void print_tree_reverse_in_order(TreeNode *root, int level) {
	if (root == NULL) return;

	// Recursively print the right subtree
	print_tree_reverse_in_order(root->right, level + 1);

	// Print the current node with indentation
	for (int i = 0; i < level; i++) {
		printf("    ");  // Print spaces for indentation
	}
	printf("%s\n", root->value);

	// Recursively print the left subtree
	print_tree_reverse_in_order(root->left, level + 1);
}
