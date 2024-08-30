/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:51:05 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/30 11:42:28 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

TreeNode	*create_node(const char *value)
{
	TreeNode	*new_node;
	
	new_node = (TreeNode *)malloc(sizeof(TreeNode));
	if (new_node == NULL)
	{
		perror("Failed to allocate memory for TreeNode");
		exit(EXIT_FAILURE);
	}
	new_node->value = ft_strdup(value);
	if (new_node->value == NULL)
	{
		perror("Failed to allocate memory for node value");
		free(new_node);
		exit(EXIT_FAILURE);
	}
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	return (new_node);
}

void	free_tree(TreeNode *node)
{
	if (node != NULL)
	{
		free_tree(node->left);
		free_tree(node->right);
		free(node->value);
		free(node);
	}
}

static char	*concat_until_pipe(t_linkedlist_node **current)
{
	char	*command;
	char	*temp;

	command = ft_strdup("");
	while (*current != NULL && ft_strncmp((*current)->data, "|", 1) != 0)
	{
		temp = ft_strjoin(command, (*current)->data);
		free(command);
		command = temp;
		if ((*current)->next != NULL && ft_strncmp((*current)->next->data, "|", 1) != 0)
		{
			temp = ft_strjoin(command, " ");
			free(command);
			command = temp;
		}
		*current = (*current)->next;
	}
	return (command);
}

TreeNode	*create_binary_tree(t_linkedlist_node *current)
{
	TreeNode	*root;
	TreeNode	*firstnode;
	char		*command;
	
	root = NULL;
	firstnode = NULL;
	command = concat_until_pipe(&current);
	if (command != NULL && ft_strlen(command) > 0)
	{
		firstnode = create_node(command);
		free(command);
	}
	if (current != NULL && ft_strncmp(current->data, "|", 1) == 0)
	{
		root = create_node(current->data);
		root->left = firstnode;
		if (firstnode != NULL)
			firstnode->parent = root;
		root->right = create_binary_tree(current->next);
	}
	else if (firstnode != NULL)
		root = firstnode;
	return (root);
}