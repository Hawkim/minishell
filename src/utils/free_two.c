/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:07:54 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 13:31:51 by nal-haki         ###   ########.fr       */
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

// free all the memory allocated by the exeution list
void	free_exe_list(char **exe)
{
	int	i;

	i = -1;
	if (!exe)
		return ;
	while (exe[++i])
		free(exe[i]);
	free(exe);
}

// free the entire t_cmd struct
//clearing the command and redirect token's list,
//the exe array and the exe_path string
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
		free_exe_list(tmp->exe);
		if (tmp->envp)
			free_envp(tmp);
		if (tmp->exe_path)
			free(tmp->exe_path);
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
