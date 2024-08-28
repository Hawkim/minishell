/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:15:21 by nal-haki          #+#    #+#             */
/*   Updated: 2024/08/28 17:37:48 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;
    char input[1024];
    char *output;
    char *out;
    t_linkedlist_node *tokens;
    t_linkedlist_node *copied;
    TreeNode *tree;
    TreeNode *tree1;

    while (1) {
        printf("minishell > ");
        fflush(stdout);  // Ensure the prompt is printed immediately

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Exit on EOF (Ctrl+D)
        }

        // Remove trailing newline character from fgets
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) {
            continue; // Skip processing if the input is empty
        }

        if (strcmp(input, "exit") == 0) {
            break; // Exit on "exit" command
        }

        output = replace_env_vars(input);
        if (!output) {
            perror("Error in replace_env_vars");
            continue;
        }

        out = replace_env_double_single(output);
        if (!out) {
            perror("Error in replace_env_double_single");
            free(output); // Free the previously allocated memory
            continue;
        }

        tokens = ftlexer(out);

        copied = copy_linked_list(tokens);
        remove_lt_and_next(&copied);

        tree = create_binary_tree(tokens);

        tree1 = create_binary_tree(copied);

        child_process(tree1, open_input_file(tokens), open_output_file(tokens), envp);

        // Free allocated memory
        free_tree(tree);
        free_tree(tree1);
        free(output);
        free(out);
    }

    return 0;
}


// // int main(int argc, char **argv, char **envp)
// // {
// // 	(void)argc;
// // 	(void)argv;
// // 	(void)envp;
// // 	// char input[] = "echo '\"'\"'\"Hello, | world!\"'\"'\"' > output.txt | grep \" \" PATH hello\"'\"a ";
// // 	// char input[] = "ls -l | wc -w $HOMEsjjfrkf$HOME";
// // 	// char input[] = " 'ls -l'";
// // 	char input[] = "echo '\"'$PATH'\"' ";
// // 	char *output = replace_env_vars(input);
// // 	if (!output) {
// //         perror("Error in replace_env_vars");
// //         return EXIT_FAILURE;
// //     }
    
// //     char *out = replace_env_double_single(output);
// //     if (!out) {
// //         perror("Error in replace_env_double_single");
// //         free(output); // Free the previously allocated memory
// //         return EXIT_FAILURE;
// //     }
// //     // Tokenize the processed string
// //     t_linkedlist_node *tokens = ftlexer(out);
// // 	// t_linkedlist_node *tokens = ftlexer(input);
// // 	printf("Tokens:\n");
// // 	print_tokens(tokens);
// // 	printf("Input file = %s\n", get_filein(tokens));
// // 	printf("Output file = %s\n", get_fileout(tokens));
// // 	t_linkedlist_node *copied = copy_linked_list(tokens);
// // 	remove_lt_and_next(&copied);
// // 	// TreeNode	*root;
// // 	// TreeNode *tree = search_tokens(tokens, envp);
// // 	TreeNode *tree = create_binary_tree(tokens);
// // 	print_tree_reverse_in_order(tree, 0);
// // 	printf("\n");
// // 	printf("\n");
// // 	printf("\n");
// // 	printf("\n");
// // 	printf("\n");
// // 	printf("\n");
// // 	printf("copied tree : \n");
// // 	TreeNode *tree1 = create_binary_tree(copied);
// // 	print_tree_reverse_in_order(tree1, 0);
// // 	printf("output :\n");
// // 	child_process(tree1, open_input_file(tokens), open_output_file(tokens), envp);
// // 	// printf("root = %s\n", tree->value);
// // 	// printf("left child = %s\n", tree->left->value);
// // 	// printf("right child = %s\n", tree->right->value);
// // 	// printf("left child of right child = %s\n", tree->right->left->value);
// // 	// printf("right child of right child = %s\n", tree->right->right->value);
// // 	// printf("parent = %s\n", tree->left->parent->value);
// // 	// move_in_tree(tree, 0);
// // 	free_tree(tree);
// // 	return 0;
// // }
