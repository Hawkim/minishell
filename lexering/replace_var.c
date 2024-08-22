/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:16:09 by nal-haki          #+#    #+#             */
/*   Updated: 2024/08/22 13:23:30 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ENV_VAR_LENGTH 256

char *replace_env_vars(const char *str) {
    size_t result_len = 0;
    size_t buffer_size = 1024;
    char *result = malloc(buffer_size);
    if (!result) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    result[0] = '\0';

    const char *pos = str;
    int in_single_quotes = 0;
    int in_double_quotes = 0;

    while (*pos) {
        if (*pos == '\'') {
            in_single_quotes = !in_single_quotes;
            if (result_len + 1 >= buffer_size) {
                buffer_size *= 2;
                char *new_result = realloc(result, buffer_size);
                if (!new_result) {
                    perror("realloc failed");
                    free(result);  // Free the previously allocated memory
                    exit(EXIT_FAILURE);
                }
                result = new_result;
            }
            result[result_len++] = *pos++;
            result[result_len] = '\0';
        } else if (*pos == '\"') {
            in_double_quotes = !in_double_quotes;
            if (result_len + 1 >= buffer_size) {
                buffer_size *= 2;
                char *new_result = realloc(result, buffer_size);
                if (!new_result) {
                    perror("realloc failed");
                    free(result);  // Free the previously allocated memory
                    exit(EXIT_FAILURE);
                }
                result = new_result;
            }
            result[result_len++] = *pos++;
            result[result_len] = '\0';
        } else if (*pos == '$' && !in_single_quotes) {
            pos++;
            const char *start = pos;
            while (*pos && (isalnum(*pos) || *pos == '_')) {
                pos++;
            }
            size_t var_len = pos - start;
            char *var_name = malloc(var_len + 1);
            if (!var_name) {
                perror("malloc failed");
                free(result);  // Free the previously allocated memory
                exit(EXIT_FAILURE);
            }
            strncpy(var_name, start, var_len);
            var_name[var_len] = '\0';

            char *env_value = getenv(var_name);
            if (env_value) {
                size_t env_value_len = strlen(env_value);
                if (env_value_len > MAX_ENV_VAR_LENGTH) {
                    // Append the variable name if it's too large
                    if (result_len + var_len + 1 >= buffer_size) {
                        buffer_size = result_len + var_len + 1;
                        char *new_result = realloc(result, buffer_size);
                        if (!new_result) {
                            perror("realloc failed");
                            free(result);  // Free the previously allocated memory
                            free(var_name);
                            exit(EXIT_FAILURE);
                        }
                        result = new_result;
                    }
                    strcat(result, "$");
                    strcat(result, var_name);
                } else {
                    if (result_len + env_value_len >= buffer_size) {
                        while (result_len + env_value_len >= buffer_size) {
                            buffer_size *= 2;
                        }
                        char *new_result = realloc(result, buffer_size);
                        if (!new_result) {
                            perror("realloc failed");
                            free(result);  // Free the previously allocated memory
                            free(var_name);
                            exit(EXIT_FAILURE);
                        }
                        result = new_result;
                    }
                    strcat(result, env_value);
                }
                result_len += strlen(result + result_len);  // Update result_len based on the actual added length
            }
            free(var_name);
        } else {
            if (result_len + 1 >= buffer_size) {
                buffer_size *= 2;
                char *new_result = realloc(result, buffer_size);
                if (!new_result) {
                    perror("realloc failed");
                    free(result);  // Free the previously allocated memory
                    exit(EXIT_FAILURE);
                }
                result = new_result;
            }
            result[result_len++] = *pos++;
            result[result_len] = '\0';
        }
    }
    return result;

}

// int main() {
//     char input[] = "  Hello '$LS_COLORS' '$PATH' '\"'$HOME'\"' '\"'$PATH'\"' ";
//     char *result = replace_env_vars(input);
//     printf("Modified input: %s\n", result);
//     free(result);  // Free the allocated memory
//     return 0;
// }
