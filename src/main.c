#include "../inc/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;
    char *input;
    char *output;
    char *out;
    t_linkedlist_node *tokens;
    t_linkedlist_node *copied;
    TreeNode *tree;
    TreeNode *tree1;

    while (1) {
        input = readline("minishell > ");
        if (input == NULL) {
            break; // Exit on EOF (Ctrl+D)
        }

        if (ft_strlen(input) == 0) {
            free(input);
            continue; // Skip processing if the input is empty
        }

        if (strcmp(input, "exit") == 0) {
            free(input);
            break; // Exit on "exit" command
        }

        output = replace_env_vars(input);
        if (!output) {
            perror("Error in replace_env_vars");
            free(input);
            continue;
        }

        out = replace_env_double_single(output);
        if (!out) {
            perror("Error in replace_env_double_single");
            free(output); // Free the previously allocated memory
            free(input);
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
        free(input);
    }

    return 0;
}
