/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:57:28 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/15 16:21:42 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct param{
	char				*s;
	int					*i;
	char				**current_token;
	t_linkedlist_node	**token_list;
	char				**state;
	int					is_pipe;
}	t_ProcessParams;

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

static void	process_character(t_ProcessParams *params)
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

static void	process_state(t_ProcessParams *params)
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

t_linkedlist_node	*ftlexer(char *s, char **envp)
{
	t_linkedlist_node	*token_list;
	char				*state;
	char				*current_token;
	int					i;

	token_list = NULL;
	state = INITIAL;
	current_token = malloc(1024);
	i = 0;
	if (!current_token)
		exit(EXIT_FAILURE);
	current_token[0] = '\0';
	// search_string(s, envp);
	t_ProcessParams params = {s, &i, &current_token, &token_list, &state};
	while (s[i] != '\0')
	{
		process_state(&params);
		i++;
	}
	append_token_if_not_empty(&current_token, &token_list);
	search_tokens(*(&token_list), envp);
	free(current_token);
	return (token_list);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to expand environment variables within single-quoted sections of a string
char *expand_env_in_single_quotes(const char *str) {
    size_t len = strlen(str);
    char *result = malloc(len * 2 + 1); // Allocate more space to handle expansion
    if (!result) return NULL;

    char *p = result;
    const char *q = str;
    int in_single_quotes = 0;

    while (*q) {
        if (*q == '\'' && (q == str || *(q - 1) != '\\')) {
            in_single_quotes = !in_single_quotes;
            *p++ = *q++;
        } else if (*q == '$' && in_single_quotes) {
            q++; // Skip '$'
            const char *start = q;
            while (*q && *q != ' ' && *q != '\'' && *q != '\"')
                q++;
            size_t var_len = q - start;
            char *var_name = strndup(start, var_len);
            if (var_name) {
                char *var_value = getenv(var_name);
                free(var_name);
                if (var_value) {
                    size_t value_len = strlen(var_value);
                    size_t current_len = p - result;
                    result = realloc(result, current_len + value_len + 1);
                    if (!result) return NULL;
                    strcpy(p, var_value);
                    p += value_len;
                }
            }
        } else {
            *p++ = *q++;
        }
    }
    *p = '\0';
    return result;
}

// Example usage
int main(int argc, char **argv, char **envp) {
    // Hardcoded input string
    char a[] = "  \"'$PWD'\"  ";

    // Expand environment variables in the input string
    char *expanded_input = expand_env_in_single_quotes(a);
    if (!expanded_input) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    // Call the lexer function with the expanded string
    t_linkedlist_node *tokens = ftlexer(expanded_input, envp);
    if (!tokens) {
        fprintf(stderr, "Error in ftlexer\n");
        free(expanded_input); // Free the expanded input string
        return EXIT_FAILURE;
    }

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

    // Free the expanded input string
    free(expanded_input);

    return EXIT_SUCCESS;
}
