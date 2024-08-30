/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:56:23 by nal-haki          #+#    #+#             */
/*   Updated: 2024/08/30 19:07:23 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void handle_signals(void)
{
    signal(SIGINT, sig_int);
    signal(SIGQUIT, SIG_IGN);
}

int main(int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;
    char *input;
    char *processed_input;
    t_linkedlist_node *tokens;
    t_linkedlist_node *copied;
    TreeNode *tree;
    TreeNode *tree1;

    sig_init();       // Initialize signal handling structures
    handle_signals(); // Set up signal handlers

    while (1) {
        input = readline("minishell > ");
        if (input == NULL) {
            // Exit on EOF (Ctrl-D)
            break;
        }

        if (ft_strlen(input) == 0) {
            free(input);
            continue; // Skip processing if the input is empty
        }

        add_history(input); // Add input to history

        processed_input = process_string(input, envp); // Expand environment variables
        if (!processed_input) {
            perror("Error in process_string");
            free(input);
            continue;
        }

        tokens = ftlexer(processed_input); // Tokenize the processed input

        if (tokens == NULL) {
            fprintf(stderr, "Error: Failed to tokenize input.\n");
            free(processed_input);
            free(input);
            continue;
        }

        // Handle built-in commands first
        if (handle_builtins(tokens)) {
            free(processed_input);
            free(input);
            continue; // Skip further processing if a built-in command was handled
        }

        // Handle redirections if no built-in command was matched
        if (differentiate_redirection(tokens)) {
            free(processed_input);
            free(input);
            continue; // Skip to the next command if redirection was handled
        }

        copied = copy_linked_list(tokens);
        remove_lt_and_next(&copied);

        tree = create_binary_tree(tokens);
        tree1 = create_binary_tree(copied);

        child_process(tree, open_input_file(tokens), open_output_file(tokens), envp);

        // Free allocated memory
        free_tree(tree);
        free_tree(tree1);
        free(processed_input);
        free(input);
    }

    return 0;
}
