/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 08:34:14 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/26 08:59:20 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define MAX_ENV_VAR_LENGTH 256

// Check if there's a pattern like '"'

bool	is_double_then_single(const char *str){
	while (*str) {
		if (*str == '"' && *(str + 1) == '\'') {
			return true;
		}
		str++;
	}
		return false;
}

char*	replace_env_double_single(const char * str) {
	if (!str) {
		return NULL;
	}

	size_t length = strlen(str);
	char *result = malloc(length * 2 + 1);
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
					free(result); // Free previously allocated memory
					exit(EXIT_FAILURE);
				}

				// Check if it's a large environment variable
				char *env_value_ptr = getenv(env_name);
				free(env_name);

				if (env_value_ptr && strlen(env_value_ptr) < MAX_ENV_VAR_LENGTH) {
					// Allocate buffer for environment variable value
					size_t env_length = strlen(env_value_ptr);
					if (res_ptr + env_length >= result + length * 2 + 1) {
						// Reallocate memory if necessary
						size_t new_length = (result + length * 2 + 1) - res_ptr + env_length;
						char *new_result = realloc(result, new_length);
						if (!new_result) {
							perror("realloc");
							free(result); // Free previously allocated memory
							exit(EXIT_FAILURE);
						}
						res_ptr = new_result + (res_ptr - result);
						result = new_result;
					}

					// Append the environment variable's value
					strcpy(res_ptr, env_value_ptr);
					res_ptr += env_length;
				} else {
					// If the environment variable is not found or is large, keep it as is
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
