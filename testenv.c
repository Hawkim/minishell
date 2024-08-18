#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Include for isalnum


#include "minishell.h"

char *replace_env_vars(const char *str) {
    char *result = malloc(1); // Start with an empty string
    result[0] = '\0';
    size_t result_len = 0;

    const char *pos = str;
    int in_single_quotes = 0;

    while (*pos) {
        if (*pos == '\'') {
            in_single_quotes = !in_single_quotes;  // Toggle single quotes state
            result_len += 1;
            result = realloc(result, result_len + 1);
            strncat(result, pos, 1);
            pos++;
        } else if (*pos == '$' && !in_single_quotes) {
            pos++; // Move past the '$'
            // Find the end of the environment variable name
            const char *start = pos;
            while (*pos && (isalnum(*pos) || *pos == '_')) {
                pos++;
            }
            size_t var_len = pos - start;
            char var_name[var_len + 1];
            strncpy(var_name, start, var_len);
            var_name[var_len] = '\0';

            // Get the environment variable value
            char *env_value = getenv(var_name);
            if (env_value) {
                // Reallocate result string with the new size
                result_len += strlen(env_value);
                result = realloc(result, result_len + 1);
                strcat(result, env_value);
            }
        } else {
            // Copy the current character to result
            result_len += 1;
            result = realloc(result, result_len + 1);
            strncat(result, pos, 1);
            pos++;
        }
    }
    
    return result;
}

// int main() {
//     const char *input = "Your home directory is \"'$HOME'\" and your shell is $SHELL";
//     char *output = replace_env_vars(input);
//     printf("%s\n", output);
//     free(output);
//     return 0;
// }
