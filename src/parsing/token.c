/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:42:04 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 11:51:22 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*create_token(char *token_value, int flag, t_minishell *g_minishell)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		free_shell(g_minishell);
		exit(12);
	}
	token->token_value = token_value;
	if (!flag)
		token->type_of_token = define_type_of_token(token_value);
	else
		token->type_of_token = WORD;
	token->next = NULL;
	return (token);
}

//split the original input line into "tokens" by spaces
//assign each element to a type_of_token defined by the  enum type_of_token 
//create a linked list of token
// Each token has a type_of_token, a token_value and a next pointer.
//  The value is the actual word, the type is the type of the word
// and the next pointer is the next token in the linked list.
int	start_tokenization(t_minishell *g_minishell)
{
	char	*input;
	size_t	i;
	size_t	prev;
	size_t	next;
	size_t	size;

	input = g_minishell->parser->input;
	i = 0;
	prev = i;
	next = i;
	size = 0;
	while (1)
	{
		if (if_token_valid(input, i, prev))
			next = i;
		size = next - prev;
		if (size > 0)
			add_to_token_list(&input[prev], size, g_minishell);
		if (!input[i])
			break ;
		prev = next;
		i++;
	}
	return (if_command_valid(g_minishell));
}
