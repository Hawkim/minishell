/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_redir_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:15:45 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 13:43:06 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_redir_valid(t_token *token)
{
	if (token->type_of_token == REDIR_IN || token->type_of_token == APPEND
		|| token->type_of_token == REDIR_OUT || token->type_of_token == HEREDOC)
	{
		if (!token->next)
		{
			print_error("syntax: ", NULL, "unexpected token.");
			g_minishell.exit_code = 2;
			return (0);
		}
		else if (token->next->type_of_token != WORD)
		{
			print_error("syntax: ", NULL, "unexpected token.");
			g_minishell.exit_code = 2;
			return (0);
		}
	}
	return (1);
}
