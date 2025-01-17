/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_grammar_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:04:39 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 12:26:12 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_grammar_valid(t_minishell *g_minishell)
{
	t_token		*token_list;
	int			i;

	i = 0;
	token_list = g_minishell->parser->tokens;
	while (token_list)
	{
		if (!if_pipe_valid (token_list, i, g_minishell)
			|| !if_redir_valid (token_list, g_minishell)
			|| !if_quotes_valid (token_list))
			return (0);
		token_list = token_list->next;
		i++;
	}
	return (1);
}
