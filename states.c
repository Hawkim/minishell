/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:22:44 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/08 12:35:50 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	append_clear(t_linkedlist_node *token_list, char *current_token)
// {
// 	if (strlen(current_token) > 0 && current_token != NULL)
// 	{
// 		// Append current token if it exists
// 		append(&token_list, current_token);
// 		current_token[0] = '\0';
// 	}
// }

void	quote_state(char *current_token, t_linkedlist_node *token_list, char *s, char *state, int i)
{
	if (s[i] == '"')
	{
	// End of quoted string
		state = INITIAL;
		strncat(current_token, &s[i], 1); // Include the closing quote
		append(&token_list, current_token);
		current_token[0] = '\0';
	}
	else
	{
	// Continue building quoted string
		strncat(current_token, &s[i], 1);
	}
}