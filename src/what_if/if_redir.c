/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:21:21 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Checks if the character is a redirection 
int	if_redir(int prev, int token_type)
{
	if (token_type == REDIR_OUT || token_type == HEREDOC
		|| token_type == REDIR_IN || token_type == APPEND
		|| prev == REDIR_OUT || prev == HEREDOC
		|| prev == REDIR_IN || prev == APPEND)
		return (1);
	return (0);
}
