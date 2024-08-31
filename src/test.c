/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 22:56:28 by nal-haki          #+#    #+#             */
/*   Updated: 2024/08/31 22:56:29 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define DOUBLE_QUOTES 1
#define SINGLE_QUOTES 2
#define between "-,+[]{}=:.?/@#%^*~"

size_t	ft_strlen(const char *s)
{
	const char	*start;

	start = s;
	while (*s++)
		;
	return (s - start - 1);
}

void	*ft_memcpy1(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dst);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dst;

	len = ft_strlen(s) + 1;
	dst = (char *)malloc(len * sizeof(char));
	if (!dst)
		return (NULL);
	ft_memcpy1(dst, s, len);
	return (dst);
}

int is_char_in_string(const char *str, char ch) {
    while (*str != '\0') {
        if (*str == ch) {
            return 1; // Character found in the string
        }
        str++;
    }
    return 0; // Character not found in the string
}

char* extract_substring(const char *str, char start_char) {
    if (!str)
        return NULL;
    // Find the starting position of the character
    const char *start_pos = strchr(str, start_char);
    if (!start_pos)
        return NULL;
    // Move start_pos to the first character after the start_char
    // start_pos++;
    // Find the end of the substring (either a space or end of string)
    const char *end_pos = start_pos + 1;
    while (*end_pos && *end_pos != ' ' && *end_pos != '\'' && *end_pos != '\"' && *end_pos != '$' && !is_char_in_string(between, *end_pos))
        end_pos++;
    // Calculate the length of the substring
    size_t length = end_pos - start_pos;
    // Allocate memory for the substring
    char *substring = malloc(length + 1);
    if (!substring)
	{
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    // Copy the substring into the newly allocated memory
    strncpy(substring, start_pos, length);
    substring[length] = '\0'; // Null-terminate the substring
    return substring;
}

char *process_string(char *str, char **env) {
    int in_single_quotes = 0; // Flag for single quotes
    int in_double_quotes = 0; // Flag for double quotes
    int i = 0;
    int j;
    char *temp_str;
    char *env_value;

    // Create a modifiable copy of the input string
    char *string = strdup(str);
    if (!string) {
        perror("strdup failed");
        exit(EXIT_FAILURE);
    }

    char *result = malloc(1024); // Allocate memory for the result string
    if (!result) {
        perror("malloc failed");
        free(string);
        exit(EXIT_FAILURE);
    }
    result[0] = '\0'; // Initialize result string

    int result_len = 0;

    while (string[i]) {
        if (string[i] == '\'') {
            // Toggle single quotes flag
            if (!in_double_quotes) {
                in_single_quotes = !in_single_quotes;
            }
            result[result_len++] = string[i];
        } else if (string[i] == '\"') {
            // Toggle double quotes flag
            if (!in_single_quotes) {
                in_double_quotes = !in_double_quotes;
            }
            result[result_len++] = string[i];
        } else if (string[i] == '$' && !in_single_quotes) {
            // Process environment variable
            int k = i ; // Start after the '$'
            temp_str = extract_substring(string + k, '$');
            // printf("EXTRACTED STRING : %s\n", temp_str);
            if (!temp_str) {
                perror("extract_substring failed");
                free(string);
                free(result);
                exit(EXIT_FAILURE);
            }
            env_value = search_env(temp_str, env);

            if (env_value) {
                // Append the environment variable value to the result
                while (*env_value) {
                    result[result_len++] = *env_value++;
                }
                // printf("22 Temp_str : %s\n", temp_str);
                // printf("22 Temp_str length: %d\n", strlen(temp_str));
                i = i + strlen(temp_str) - 1;
            } else {
                // If no environment variable found, keep '$'
            if (!env_value)
            {
                if (strncmp(temp_str, "$", strlen(temp_str)) == 0){
                    result[result_len++] = '$';result[result_len++] = ' ';
                    i = i + strlen(temp_str);}
                i = i + strlen(temp_str) - 1;
            }
            }
            free(temp_str);
          } else {
            // Copy regular characters
            result[result_len] = string[i];
            result_len++;
        }
        i++;
    }

    result[result_len] = '\0'; // Null-terminate the result string

    free(string);
    return (result);
    free(result);
}