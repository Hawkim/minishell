#include "minishell.h"

t_linkedlist_node *ftlexer(char *s) {
    t_linkedlist_node    *token_list = NULL; // List of tokens
    char                *state = INITIAL; // Current state of the lexer
    char                *current_token = NULL; // Buffer for the current token
    int                 i = 0;
    char                last_quote = 0;

    current_token = malloc(1024);
    if (!current_token) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    current_token[0] = '\0'; // Initialize buffer

    while (s[i] != '\0') {
        if (strcmp(state, INITIAL) == 0) {
            if (s[i] == ' ') {
                if (strlen(current_token) > 0) {
                    append(&token_list, current_token);
                    current_token = malloc(1024);
                    if (!current_token) {
                        perror("malloc failed");
                        exit(EXIT_FAILURE);
                    }
                    current_token[0] = '\0';
                }
                i++;
                continue;
            } else if (s[i] == '\"') {
                if (strlen(current_token) > 0) {
                    append(&token_list, current_token);
                    current_token = malloc(1024);
                    if (!current_token) {
                        perror("malloc failed");
                        exit(EXIT_FAILURE);
                    }
                    current_token[0] = '\0';
                }
                state = IN_QUOTE;
                last_quote = s[i];
            } else if (s[i] == '\'') {
                if (strlen(current_token) > 0) {
                    append(&token_list, current_token);
                    current_token = malloc(1024);
                    if (!current_token) {
                        perror("malloc failed");
                        exit(EXIT_FAILURE);
                    }
                    current_token[0] = '\0';
                }
                state = IN_SQUOTE;
                last_quote = s[i];
            } else if (strchr("|><&", s[i])) {
                if (strlen(current_token) > 0) {
                    append(&token_list, current_token);
                    current_token = malloc(1024);
                    if (!current_token) {
                        perror("malloc failed");
                        exit(EXIT_FAILURE);
                    }
                    current_token[0] = '\0';
                }
                char op[2] = {s[i], '\0'};
                append(&token_list, op);
            } else {
                strncat(current_token, &s[i], 1);
            }
        } else if (strcmp(state, IN_QUOTE) == 0) {
            if (s[i] == '"') {
                state = INITIAL;
                if (strlen(current_token) > 0) {
                    if (current_token != "\'")
                        append(&token_list, current_token);
                    current_token = malloc(1024);
                    if (!current_token) {
                        perror("malloc failed");
                        exit(EXIT_FAILURE);
                    }
                    current_token[0] = '\0';
                }
            } else {
                strncat(current_token, &s[i], 1);
            }
        } else if (strcmp(state, IN_SQUOTE) == 0) {
            if (s[i] == '\'') {
                state = INITIAL;
                if (strlen(current_token) > 0) {
                    append(&token_list, current_token);
                    current_token = malloc(1024);
                    if (!current_token) {
                        perror("malloc failed");
                        exit(EXIT_FAILURE);
                    }
                    current_token[0] = '\0';
                }
            } else {
                strncat(current_token, &s[i], 1);
            }
        }
        i++;
    }

    if (strlen(current_token) > 0) {
        append(&token_list, current_token);
    }
    free(current_token); // Free the allocated buffer
    return token_list;
}

int main() {
    char input[] = "echo \"'\"\"Hello, world!\"\"'\" > output.txt | grep hello '''helloo''' ";

    // Call the lexer function
    t_linkedlist_node *tokens = ftlexer(input);

    // Print the tokens
    printf("Tokens:\n");
    print_tokens(tokens);

    // Free the linked list
    t_linkedlist_node *current = tokens;
    t_linkedlist_node *next;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    return 0;
}
