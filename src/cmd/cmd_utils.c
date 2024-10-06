/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:49:33 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/01 18:27:40 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//add a new t_command cmd to the back of the linked list

void	add_cmd_back(t_command *cmd)
{
	t_command	*cmd_list;

	cmd_list = g_minishell.command;
	if (!cmd_list)
		g_minishell.command = cmd;
	else
	{
		while (cmd_list->next)
			cmd_list = cmd_list->next;
		cmd_list->next = cmd;
	}
}

void	set_cmd_endp(t_command **cmd, t_token **list, int *prev)
{
	t_token	**position;

	while (*list && (*list)->token_type < PIPE)
	{
		position = &(*cmd)->commands;
		if (if_redir(*prev, (*list)-> token_type))
			position = &(*cmd)->redirections;
		add_back_tkn (position, token_dup(*list));
		(*prev) = (*list)->token_type;
		(*list) = (*list)->next;
	}
	if (*list)
	{
		(*cmd)->endpoint = (*list)->token_type;
		(*prev) = (*list)->token_type;
		(*list) = (*list)-> next;
	}
}
