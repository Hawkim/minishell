/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:57:28 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/09 17:00:32 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// int main(int argc, char **argv, char **envp)
// {
// 	char input[] = "echo '\"'\"'\"Hello, | world!\"'\"'\"' > output.txt | grep $ddd \"hello\"\"a\" ";
// 	char   a[] = "$PATH";
// 	// Call the lexer function
// 	t_linkedlist_node *tokens = ftlexer(a);

// 	(void)argv;
// 	(void)argc;
// 	// Print the tokens
// 	printf("Tokens:\n");
// 	print_tokens(tokens);

// 	// Free the linked list
// 	t_linkedlist_node *current = tokens;
// 	t_linkedlist_node *next;
// 	while (current != NULL) {
// 		next = current->next;
// 		free(current->data);
// 		free(current);
// 		current = next;
// 	}

// 	return 0;
// }
