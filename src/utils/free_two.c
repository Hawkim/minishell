/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:07:54 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/27 17:20:29 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_envp(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->envp[++i])
		free(cmd->envp[i]);
	free(cmd->envp);
	cmd->envp = NULL;
}

void	free_expansion(char **str, char *next)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	if (next)
		free(next);
}

// free all the memory allocated by the execution list
void	free_exec_list(char **exec)
{
	int	i;

	i = -1;
	if (!exec)
		return ;
	while (exec[++i])
		free(exec[i]);
	free(exec);
}

// free the entire t_cmd struct
//clearing the command and redirect token's list,
//the exec array and the exec_path string
void	free_command(void)
{
	t_command	*curr;
	t_command	*tmp;

	curr = g_minishell.command;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free_tokens(&tmp->commands);
		free_tokens(&tmp->redirections);
		free_exec_list(tmp->exec);
		if (tmp->envp)
			free_envp(tmp);
		if (tmp->exec_path)
			free(tmp->exec_path);
		free(tmp);
	}
	g_minishell.command = NULL;
}

void	free_tokens(t_token **tokens)
{
	t_token	*token;
	t_token	*temp;

	token = *tokens;
	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->token_value);
		free(temp);
	}
	*tokens = NULL;
}
