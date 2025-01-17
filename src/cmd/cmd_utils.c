/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:49:33 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 13:16:54 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//add a new t_command cmd to the back of the linked list

void	add_cmd_back(t_command *cmd, t_minishell *g_minishell)
{
	t_command	*cmd_list;

	cmd_list = g_minishell->command;
	if (!cmd_list)
		g_minishell->command = cmd;
	else
	{
		while (cmd_list->next)
			cmd_list = cmd_list->next;
		cmd_list->next = cmd;
	}
}

void	set_cmd_endp(t_command **cmd, t_token **list, int *prev,
	t_minishell **g_minishell)
{
	t_token	**position;

	while (*list && (*list)->type_of_token < PIPE)
	{
		position = &(*cmd)->commands;
		if (if_redir(*prev, (*list)-> type_of_token))
			position = &(*cmd)->redirections;
		add_back_tkn (position, token_dup(*list, *g_minishell));
		(*prev) = (*list)->type_of_token;
		(*list) = (*list)->next;
	}
	if (*list)
	{
		(*cmd)->endpoint = (*list)->type_of_token;
		(*prev) = (*list)->type_of_token;
		(*list) = (*list)-> next;
	}
}
