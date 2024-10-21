/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:42:04 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 13:43:06 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//The flag which indicates
//if the string will pass through the grammar check (0) or not (1)
// If it is, defined the type_of_token enum with the define_type_of_token function.
// return to new node token
t_token	*create_token(char *token_value, int flag)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		free_shell();
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
int	start_tokenization(void)
{
	char	*input;
	size_t	i;
	size_t	prev;
	size_t	next;
	size_t	size;

	input = g_minishell.parser->input;
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
			add_to_token_list(&input[prev], size);
		if (!input[i])
			break ;
		prev = next;
		i++;
	}
	return (if_command_valid());
}
