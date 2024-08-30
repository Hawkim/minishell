/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:07:16 by nal-haki          #+#    #+#             */
/*   Updated: 2024/08/30 15:07:23 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void handle_signals(void)
{
    signal(SIGINT, sig_int);
    signal(SIGQUIT, SIG_IGN);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;
    char *input;
    char *output;
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

        if (strcmp(input, "exit") == 0) {
            free(input);
            break; // Exit on "exit" command
        }

        output = process_string(input, envp);
        if (!output) {
            perror("Error in process_string");
            free(input);
            continue;
        }

        tokens = ftlexer(output);
        if (differentiate_redirection(tokens))
        {
            free(output);
            free(input);
            continue;  // Skip to the next command
        }

        copied = copy_linked_list(tokens);
        remove_lt_and_next(&copied);

        tree = create_binary_tree(tokens);
        tree1 = create_binary_tree(copied);

        child_process(tree, open_input_file(tokens), open_output_file(tokens), envp);

        // Free allocated memory
        free_tree(tree);
        free_tree(tree1);
        free(output);
        free(input);
    }

    return 0;
}
