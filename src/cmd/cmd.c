/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:04:58 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/05 01:39:37 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//It will malloc and create a new t_cmd node, which is is a structure that
//will be further populated by a simple command data (here pointing to NULL).

//exit 12 -> Cannot allocate memory

t_command	*cmd_create(int id)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		free_minishell();
		exit(12);
	}
	cmd->id = id;
	cmd->commands = NULL;
	cmd->redirections = NULL;
	cmd->endpoint = -1;
	cmd->is_piped = 0;
	cmd->exec = NULL;
	cmd->exec_path = NULL;
	cmd->envp = NULL;
	cmd->fd_in = -2;
	cmd->fd_out = -2;
	cmd->next = NULL;
	return (cmd);
}

// toke list len
size_t	token_list_len(t_token *list)
{
	size_t	len;

	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}

char	**token_to_str(t_token *token)
{
	size_t		size;
	char		**list;
	int			i;

	size = token_list_len(token) + 1;
	list = ft_calloc(sizeof(char *), size);
	if (!list)
	{
		free_minishell();
		exit(11);
	}
	i = 0;
	while (token)
	{
		list[i] = ft_strdup(token->token_value);
		token = token->next;
		i++;
	}
	return (list);
}

//prepare the array of strings to be executed
//by iterating through the command structure 
//convert each token into an array of strings
void	command_list(void)
{
	t_command	*cmd;

	cmd = g_minishell.command;
	while (cmd)
	{
		cmd->exec = token_to_str(cmd->commands);
		cmd = cmd->next;
	}
}

//assemble the t_tkn list into two different commands and redirect list,
//using the operators as endpoints to simple commands
// take the token list and fill the command table
// init the command 
// send to set_command_endpoints to fill the command 
// redirect list
// add the endpoint to the command struct

void	command_table(void)
{
	t_command	*cmd_node;
	t_token		*token_list;
	int			prev;
	int			i;

	token_list = g_minishell.parser->tokens;
	prev = -1;
	i = 0;
	while (token_list)
	{
		cmd_node = cmd_create(i);
		set_cmd_endp(&cmd_node, &token_list, &prev);
		add_cmd_back(cmd_node);
		i++;
	}
	expand_cmd();
	command_list();
}