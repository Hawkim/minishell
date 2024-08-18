#include "minishell.h"

// Define the list of large environment variables
const char *large_env_vars[] = {
    "PATH",
    "LS_COLORS",
    // Add other large env variables here
    NULL
};

// Check if a token is a large environment variable
int is_large_env_var(const char *token) {
    for (int i = 0; large_env_vars[i] != NULL; i++) {
        if (strcmp(token, large_env_vars[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Get the value of an environment variable
char *get_env_value(const char *var_name) {
    char *env_value = getenv(var_name);
    if (env_value) {
        return strdup(env_value);
    }
    return NULL;
}

// Replace a token with the value of the corresponding environment variable
void replace_token(t_linkedlist_node *node) {
    if (node == NULL || node->data[0] != '$') {
        return;
    }
    
    char *var_name = node->data + 1; // Skip the '$'
    char *env_value = get_env_value(var_name);
    
    if (env_value) {
        free(node->data); // Free the old token data
        node->data = env_value; // Replace with the new value
    } else {
        // Optionally, handle the case where the environment variable is not found
        printf("Environment variable not found: %s\n", var_name);
    }
}

// Replace large environment variable tokens in the linked list
t_linkedlist_node *replace_large_env_vars(t_linkedlist_node *tokens) {
    t_linkedlist_node *current = tokens;
    while (current != NULL) {
        if (current->data[0] == '$' && is_large_env_var(current->data + 1)) {
            replace_token(current);
        }
        current = current->next;
    }
    return tokens;
}
