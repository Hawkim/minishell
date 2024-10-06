/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_redir_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:15:45 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/27 17:23:48 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_redir_valid(t_token *token)
{
	if (token->token_type == REDIR_IN || token->token_type == APPEND
		|| token->token_type == REDIR_OUT || token->token_type == HEREDOC)
	{
		if (!token->next)
		{
			print_error("syntax: ", NULL, "unexpected token.");
			g_minishell.exit_code = 2;
			return (0);
		}
		else if (token->next->token_type != WORD)
		{
			print_error("syntax: ", NULL, "unexpected token.");
			g_minishell.exit_code = 2;
			return (0);
		}
	}
	return (1);
}
