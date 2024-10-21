/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:21:21 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 13:43:06 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Checks if the character is a redirection 
int	if_redir(int prev, int type_of_token)
{
	if (type_of_token == REDIR_OUT || type_of_token == HEREDOC
		|| type_of_token == REDIR_IN || type_of_token == APPEND
		|| prev == REDIR_OUT || prev == HEREDOC
		|| prev == REDIR_IN || prev == APPEND)
		return (1);
	return (0);
}
