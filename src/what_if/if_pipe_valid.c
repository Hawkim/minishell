/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_pipe_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:06:34 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//check pipe position or follow by cmd

int	if_pipe_valid(t_token *token, int pos)
{
	if (token->token_type == PIPE)
	{
		if (pos == 0 || !token->next
			|| !ft_strncmp(token->next->token_value, "|", 1))
		{
			print_error("syntax:", NULL, " : unexpected token.");
			g_minishell.exit_code = 2;
			return (0);
		}
	}
	return (1);
}