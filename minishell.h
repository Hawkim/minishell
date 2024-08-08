/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:39:40 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/08 12:35:15 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

# define INITIAL "INITIAL"
# define IN_QUOTE "IN_QUOTE"
# define IN_SQUOTE "IN_SQUOTE"
# define IN_ESCAPE "IN_ESCAPE"

typedef struct ll_node
{
	struct ll_node	*next;
	char			*data;
	char			*state;
}	t_linkedlist_node;

t_linkedlist_node	*ftlexer(char *s);
void				append(t_linkedlist_node **token_list, char *s);
void 				print_tokens(t_linkedlist_node *list);
void				quote_state(char *current_token, t_linkedlist_node *token_list, char *s, char *state, int i);
void				append_clear(t_linkedlist_node *token_list, char *current_token);

#endif