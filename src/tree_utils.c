/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:38:47 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/30 18:32:51 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int differentiate_redirection(t_linkedlist_node *token_list) {
    int count_left = 0;
    int count_right = 0;

    t_linkedlist_node *current = token_list;

    while (current != NULL && current->next != NULL) {
        if (strcmp(current->data, "<") == 0 && strcmp(current->next->data, "<") == 0) {
            count_left++;
        } else if (strcmp(current->data, ">") == 0) {
            count_right++;
        }
        current = current->next;
    }
    if (count_left == 1)
	{
        if (count_right == 1 || count_right == 2)
            heredoc_input(token_list);
        else if (count_right == 0)
			open_heredoc_one(token_list);
		return (1);
    }
	else {
        return 0;
    }
}

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	// char input[] = "echo '\"'\"'\"Hello, | world!\"'\"'\"' > output.txt | grep \" \" PATH hello\"'\"a ";
// 	// char input[] = "ls -l | wc -w $HOMEsjjfrkf$HOME";
// 	// char input[] = " 'ls -l'";
// 	char input[] = "echo $$";
// 	char *input1 = process_string(input, envp);
// 	printf("INPUT : %s\n", input1);
// 	// char *output = replace_env_vars(input);
// 	// if (!output) {
//     //     perror("Error in replace_env_vars");
//     //     return EXIT_FAILURE;
//     // }
    
//     // char *out = replace_env_double_single(output);
//     // if (!out) {
//     //     perror("Error in replace_env_double_single");
//     //     free(output); // Free the previously allocated memory
//     //     return EXIT_FAILURE;
//     // }
//     // Tokenize the processed string
//     t_linkedlist_node *tokens = ftlexer(input1);
// 	if(differentiate_redirection(tokens))
// 		return (0);
// 	// t_linkedlist_node *tokens = ftlexer(input);
// 	printf("Tokens:\n");
// 	print_tokens(tokens);
// 	// printf("HEREDOCDEl : %s\n", get_heredoc_delimiter(tokens));
// 	// printf("Input file = %s\n", get_filein(tokens));
// 	// printf("Output file = %s\n", get_fileout(tokens));
// 	// printf("HEREDOC = %s\n", get_heredoc_file(tokens));
// 	t_linkedlist_node *copied = copy_linked_list(tokens);
// 	remove_lt_and_next(&copied);
// 	// TreeNode	*root;
// 	// TreeNode *tree = search_tokens(tokens, envp);
// 	TreeNode *tree = create_binary_tree(tokens);
// 	print_tree_reverse_in_order(tree, 0);
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
// 	printf("copied tree : \n");
// 	TreeNode *tree1 = create_binary_tree(copied);
// 	print_tree_reverse_in_order(tree1, 0);
// 	printf("output :\n");
// 	child_process(tree1, open_input_file(tokens), open_output_file(tokens), envp);
// 	// printf("root = %s\n", tree->value);
// 	// printf("left child = %s\n", tree->left->value);
// 	// printf("right child = %s\n", tree->right->value);
// 	// printf("left child of right child = %s\n", tree->right->left->value);
// 	// printf("right child of right child = %s\n", tree->right->right->value);
// 	// printf("parent = %s\n", tree->left->parent->value);
// 	// move_in_tree(tree, 0);
// 	free_tree(tree);
// 	return 0;
// }
