/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_quotes_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:35:03 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/13 16:04:47 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// check if quotations marks are correct ( single & double quote)
// quotation marks are valid
// exit 2 -> terminate the calling process

int	skip_line(void)
{
	print_error("quotes", ">", " \':EOF while expecting quote\n");
	return (0);
}

int	if_quotes_valid(t_token *token)
{
	int	is_in_quote;
	int	i;

	is_in_quote = -1;
	i = 0;
	if (!token->next)
	{
		while (token->token_value [i])
		{
			if (is_in_quote == -1 && (token->token_value[i] == '\''
					|| token->token_value[i] == '\"'))
				is_in_quote = i;
			else if (is_in_quote != -1
				&& token->token_value[i] == token->token_value[is_in_quote])
				is_in_quote = -1;
			i++;
		}
		if (is_in_quote != -1)
			return (skip_line());
	}
	return (1);
}
