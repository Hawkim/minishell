/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:57:28 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/18 02:48:15 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>
typedef	struct	{
	char				*s;
	int					*i;
	char				**current_token;
	t_linkedlist_node	**token_list;
	char				**state;
} ProcessParams;

static void	reset_current_token(char **current_token)
{
	free(*current_token);
	*current_token = malloc(1024);
	if (!*current_token)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	(*current_token)[0] = '\0';
}

static void	append_token_if_not_empty(char **current_token,
					t_linkedlist_node **token_list)
{
	if (strlen(*current_token) > 0)
	{
		append(token_list, *current_token);
		reset_current_token(current_token);
	}
}

static void	handle_space(char **current_token, t_linkedlist_node **token_list)
{
	append_token_if_not_empty(current_token, token_list);
}

static void	handle_operator(char **current_token,
					t_linkedlist_node **token_list, char op)
{
	char	operator[2];

	append_token_if_not_empty(current_token, token_list);
	operator[0] = op;
	operator[1] = '\0';
	append(token_list, operator);
}

static void	process_character(ProcessParams *params)
{
	if (params->s[*params->i] == ' ')
		handle_space(params->current_token, params->token_list);
	else if (params->s[*params->i] == '\"')
		*params->state = IN_QUOTE;
	else if (params->s[*params->i] == '\'')
		*params->state = IN_SQUOTE;
	else if (strchr("|><&", params->s[*params->i]))
		handle_operator(params->current_token,
			params->token_list, params->s[*params->i]);
	else
		strncat(*params->current_token, &params->s[*params->i], 1);
}

static void	process_state(ProcessParams *params)
{
	if (strcmp(*params->state, INITIAL) == 0)
		process_character(params);
	else if (strcmp(*params->state, IN_QUOTE) == 0)
	{
		if (params->s[*params->i] == '\"')
			*params->state = INITIAL;
		else
			strncat(*params->current_token, &params->s[*params->i], 1);
	}
	else if (strcmp(*params->state, IN_SQUOTE) == 0)
	{
		if (params->s[*params->i] == '\'')
			*params->state = INITIAL;
		else
			strncat(*params->current_token, &params->s[*params->i], 1);
	}
}
char *process_and_expand(const char *input) {
    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (!result) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    size_t result_len = 0;
    
    int in_single_quotes = 0;
    int in_double_quotes = 0;
    const char *pos = input;

    while (*pos) {
        if (*pos == '\'') {
            in_single_quotes = !in_single_quotes;
            result[result_len++] = *pos++;
        } else if (*pos == '\"') {
            in_double_quotes = !in_double_quotes;
            result[result_len++] = *pos++;
        } else if (*pos == '$' && !in_single_quotes) {
            pos++;
            const char *start = pos;
            while (*pos && (isalnum(*pos) || *pos == '_')) {
                pos++;
            }
            size_t var_len = pos - start;
            char var_name[var_len + 1];
            strncpy(var_name, start, var_len);
            var_name[var_len] = '\0';

            char *env_value = getenv(var_name);
            if (env_value) {
                size_t env_len = strlen(env_value);
                result = realloc(result, result_len + env_len + 1);
                if (!result) {
                    perror("realloc failed");
                    exit(EXIT_FAILURE);
                }
                memcpy(result + result_len, env_value, env_len);
                result_len += env_len;
            }
        } else {
            result[result_len++] = *pos++;
        }
    }
    result[result_len] = '\0';
    
    // Adjust the quotes to reflect the actual content
    // Ensure nested quotes are properly handled
    char *final_result = malloc(result_len + 1);
    if (!final_result) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    
    size_t final_len = 0;
    in_single_quotes = 0;
    in_double_quotes = 0;
    pos = result;

    while (*pos) {
        if (*pos == '\'' && !in_double_quotes) {
            in_single_quotes = !in_single_quotes;
            final_result[final_len++] = *pos++;
        } else if (*pos == '\"' && !in_single_quotes) {
            in_double_quotes = !in_double_quotes;
            final_result[final_len++] = *pos++;
        } else {
            final_result[final_len++] = *pos++;
        }
    }
    final_result[final_len] = '\0';

    free(result);
    return final_result;
}

t_linkedlist_node	*ftlexer(char *s)
{
	t_linkedlist_node	*token_list;
	char				*state;
	char				*current_token;
	int					i;

	if (!current_token)
		exit(EXIT_FAILURE);
	token_list = NULL;
	state = INITIAL;
	current_token = malloc(1024);
	i = 0;
	current_token[0] = '\0';
	ProcessParams params = {s, &i, &current_token, &token_list, &state};
	while (s[i] != '\0')
	{
		process_state(&params);
		i++;
	}
	append_token_if_not_empty(&current_token, &token_list);
	free(current_token);
	return (token_list);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// Function to remove the outermost double and single quotes
char *strip_outer_quotes(const char *str) {
    size_t len = strlen(str);

    // Check if the string starts and ends with double quotes
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        // Allocate new string without the outer double quotes
        char *result = malloc(len - 1);
        if (!result) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        strncpy(result, str + 1, len - 2);
        result[len - 2] = '\0';

        // Remove single quotes if they are the outermost quotes
        len = strlen(result);
        if (len >= 2 && result[0] == '\'' && result[len - 1] == '\'') {
            char *inner_result = malloc(len - 1);
            if (!inner_result) {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }
            strncpy(inner_result, result + 1, len - 2);
            inner_result[len - 2] = '\0';
            free(result);
            return inner_result;
        }
        return result;
    }
    // Return a copy of the original string if no outer quotes
    return strdup(str);
}

// Function to expand environment variables
char *expand_env_vars(const char *str) {
    char *result = malloc(1);
    result[0] = '\0';
    size_t result_len = 0;

    const char *pos = str;
    int in_single_quotes = 0;

    while (*pos) {
        if (*pos == '\'') {
            in_single_quotes = !in_single_quotes;
            result_len += 1;
            result = realloc(result, result_len + 1);
            strncat(result, pos, 1);
            pos++;
        } else if (*pos == '$' && !in_single_quotes) {
            pos++;
            const char *start = pos;
            while (*pos && (isalnum(*pos) || *pos == '_')) {
                pos++;
            }
            size_t var_len = pos - start;
            char var_name[var_len + 1];
            strncpy(var_name, start, var_len);
            var_name[var_len] = '\0';

            char *env_value = getenv(var_name);
            if (env_value) {
                result_len += strlen(env_value);
                result = realloc(result, result_len + 1);
                strcat(result, env_value);
            }
        } else {
            result_len += 1;
            result = realloc(result, result_len + 1);
            strncat(result, pos, 1);
            pos++;
        }
    }

    return result;
}

// Function to simulate `echo` behavior with nested quotes
char *simulate_echo(const char *input) {
    // Step 1: Strip outermost quotes
    char *stripped_input = strip_outer_quotes(input);
    
    // Step 2: Expand environment variables
    char *expanded = expand_env_vars(stripped_input);

    // Step 3: Handle nested quotes
    size_t len = strlen(expanded);
    char *final_result = malloc(len + 1);
    if (!final_result) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    size_t final_len = 0;
    int in_single_quotes = 0;

    for (size_t i = 0; i < len; i++) {
        if (expanded[i] == '\'') {
            in_single_quotes = !in_single_quotes;
            final_result[final_len++] = expanded[i];
        } else if (expanded[i] == '"') {
            final_result[final_len++] = expanded[i];
        } else {
            final_result[final_len++] = expanded[i];
        }
    }
    final_result[final_len] = '\0';

    free(expanded);
    free(stripped_input);

    return final_result;
}

int main(int argc, char **argv)
{
	char input[] = "echo '\"'\"'\"Hello, | world!\"'\"'\"' > output.txt | grep $ddd \"hello\"\"a\"  $HOME";
	
	
	char   a[] = " hello man \"HOMEdad\"213 '$HOME'  \"$HOME\"   '\"$HOME\"'  \"'$HOME'\" ";


char* first_output=expand_env_vars(a);
	printf("%s\n",first_output);

	// Call the lexer function
char* output= process_and_expand(first_output);
	printf("%s\n",output);
	t_linkedlist_node *tokens = ftlexer(output);

	(void)argv;
	(void)argc;
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