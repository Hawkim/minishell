/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testcase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:57:28 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/22 15:38:27 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_linkedlist_node *ftlexer(char *s) {
    t_linkedlist_node *token_list = NULL;
    char *state = INITIAL; // Ensure `state` is properly initialized
    char *current_token = malloc(1024);
    if (!current_token) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    current_token[0] = '\0'; // Initialize first character

    int i = 0;
    ProcessParams params = {s, &i, &current_token, &token_list, &state};

    while (s[i] != '\0') {
        process_state(&params);
        i++;
    }

    append_token_if_not_empty(&current_token, &token_list);
    free(current_token); // Ensure to free allocated memory

    return token_list;
}


int main(int argc, char **argv) {
    // Input string for processing
    char input[] = " '\"'$HOME'\"' \"'PA             TH'\"   <b   \"Hello\"ddddd '$PATH' \"'$PAdasdasdTH'\"  \"'$HOME'\" ";

    // Replace environment variables and handle quotes
    char *output = replace_env_vars(input);
    if (!output) {
        perror("Error in replace_env_vars");
        return EXIT_FAILURE;
    }
    
    char *out = replace_env_double_single(output);
    if (!out) {
        perror("Error in replace_env_double_single");
        free(output); // Free the previously allocated memory
        return EXIT_FAILURE;
    }
    
    // Tokenize the processed string
    t_linkedlist_node *tokens = ftlexer(out);
    if (!tokens) {
        perror("Error in ftlexer");
        free(output);
        free(out);
        return EXIT_FAILURE;
    }

    // Print tokens
    printf("Tokens:\n");
    print_tokens(tokens);

    // Clean up
    free(output);
    free(out);

    // Free the linked list
    t_linkedlist_node *current = tokens;
    t_linkedlist_node *next;
    while (current != NULL) {
        next = current->next;
        free(current->data); // Assuming data is dynamically allocated
        free(current);
        current = next;
    }

    (void)argv;
    (void)argc;

    return EXIT_SUCCESS;
}