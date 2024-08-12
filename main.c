#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

int main() {
    char *input = NULL;
    size_t len = 0;

    while (1) {
        // Print the prompt
        printf("minishell> ");
        
        // Read the input
        getline(&input, &len, stdin);
        
        // Handle exit or quit commands
        if (strcmp(input, "exit\n") == 0 || strcmp(input, "quit\n") == 0) {
            break;
        }

        // Tokenize the input
        t_linkedlist_node *tokens = ftlexer(input);

        // Parse and execute the commands
        parse_and_execute(tokens);

        // Free the token list if needed
        // free_token_list(tokens);
    }

    // Free the input buffer
    free(input);
    return 0;
}
