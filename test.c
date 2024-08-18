#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_double_then_single(const char *str) {
    // Check if there's a pattern like '"'
    while (*str) {
        if (*str == '"' && *(str + 1) == '\'') {
            return true;
        }
        str++;
    }
    return false;
}

char* replace_env_variables(const char *str) {
    if (!str) {
        return NULL;
    }

    size_t length = strlen(str);
    char *result = malloc(length * 2 + 1); // Allocate more memory to be safe
    if (!result) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char *res_ptr = result;

    while (*str) {
        if (*str == '"' && *(str + 1) == '\'') {
            // Copy the double quote and single quote
            *res_ptr++ = *str++;
            *res_ptr++ = *str++;

            // Process the content between the quotes
            const char *start = str;
            while (*str && *str != '\'') {
                str++;
            }

            if (str > start && *start == '$') {
                // Extract the environment variable name
                char *env_name = strndup(start + 1, str - start - 1);
                if (!env_name) {
                    perror("strndup");
                    exit(EXIT_FAILURE);
                }

                char *env_value = getenv(env_name);
                free(env_name);

                if (env_value) {
                    // Allocate enough space for the environment variable value
                    size_t env_length = strlen(env_value);
                    if (res_ptr + env_length >= result + length * 2 + 1) {
                        // Reallocate memory if necessary
                        size_t new_length = length * 2 + 1 + env_length;
                        char *new_result = realloc(result, new_length);
                        if (!new_result) {
                            perror("realloc");
                            exit(EXIT_FAILURE);
                        }
                        res_ptr = new_result + (res_ptr - result);
                        result = new_result;
                    }

                    // Append the environment variable's value
                    strcpy(res_ptr, env_value);
                    res_ptr += env_length;
                } else {
                    // If the environment variable is not found, keep it as is
                    strncpy(res_ptr, start, str - start);
                    res_ptr += str - start;
                }
            } else {
                // No environment variable, just copy the text as is
                strncpy(res_ptr, start, str - start);
                res_ptr += str - start;
            }

            // Copy the closing single quote
            if (*str == '\'') {
                *res_ptr++ = *str++;
            }

            // Copy the closing double quote
            if (*str == '"') {
                *res_ptr++ = *str++;
            }
        } else {
            // Copy any other character
            *res_ptr++ = *str++;
        }
    }

    *res_ptr = '\0';
    return result;
}

int main() {
    char input[] = "   \"'$PATH'\" ddd  | grep pitput.txt dasdsads echo '\"'\"'\"Hello, | world!\"'\"'\"' > output.txt | grep $ddd \"hello\"\"a\"  $HOME \"'$HOME'\"  2313213 $DADDA \"'$HOME'\"  \"'$HOME'\" \"'$HOME'\" \"'$HOME'\"     $HOME                   $HOME        $HOME         $HOME  \"'$HOME'\"";
     
    if (is_double_then_single(input)) {
        char *result = replace_env_variables(input);
        printf("Result: %s\n", result);
        free(result);
    } else {
        printf("No matching quotes found.\n");
    }

    return 0;
}
