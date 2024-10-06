/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:21:27 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/27 17:15:18 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**split_variable_expansion(char	*expansion)
{
	char	**result;

	if (!expansion)
	{
		result = malloc (sizeof(char *) * 1);
		result[0] = NULL;
	}
	else
		result = ft_split(expansion, ' ');
	if (expansion)
		free(expansion);
	return (result);
}

void	expand_param(t_token **token, int *index, int i)
{
	char	*prev;
	char	*next;
	char	**expansion_split;
	t_token	*last;

	if (!if_expandable ((*token)->token_value[(*index) + 1]))
		return ;
	prev = ft_strndup ((*token)->token_value, (*index)++);
	expansion_split = parameter_expansion(*token, index);
	next = ft_strdup(&(*token)->token_value[*index]);
	last = (*token)->next;
	(*token)->next = NULL;
	free ((*token)->token_value);
	(*token)->token_value = ft_strjoin (prev, expansion_split[i]);
	while (expansion_split[0] && expansion_split[++i])
		add_back_tkn(token, create_token(ft_strdup(expansion_split[i]), 1));
	while ((*token)->next)
		(*token) = (*token)->next;
	free(prev);
	prev = (*token)->token_value;
	(*token)->token_value = ft_strjoin(prev, next);
	free(prev);
	(*index) = ft_strlen(expansion_split[i]) - 1;
	(*token)->next = last;
	free_expansion(expansion_split, next);
}

// with the exception of "<<" 
// jump to the next token and
// expand any dollar sign and quotes in the token
void	expand_redir(t_command *cmd)
{
	t_token	*token;

	token = cmd->redirections;
	while (token)
	{
		if (ft_strncmp(token->token_value, "<<", 3))
		{
			token = token->next;
			expand_token(&token);
		}
		else
			token = token->next;
		token = token->next;
	}
}

//iterate through the char* string "token_value"
// if dollar sign, replace it expand parameter;
// if quote sign, treat it as a string & expand with expand quotes

void	expand_token(t_token **token)
{
	int	i;

	i = 0;
	while ((*token)->token_value[i])
	{
		if (!ft_strncmp ("$EMPTY", (*token)->token_value, 5))
			rl_on_new_line();
		if ((*token)->token_value[i] == '$')
			expand_param (token, &i, 0);
		else if ((*token)->token_value[i] == '\"'
			|| (*token)->token_value[i] == '\'')
			expand_quotes(token, &i, (*token)->token_value[i], 0);
		i++;
	}
}

//change the nodes of the token list into shell's grammar
// variable expansion according to the environment
// and local variables (prompted by '$')
// quotation expansion
// upon open and closing quotation marks

void	expand_cmd(void)
{
	t_command	*cmd;
	t_token		*token;

	cmd = g_minishell.command;
	while (cmd)
	{
		token = cmd->commands;
		while (token)
		{
			expand_token(&token);
			token = token->next;
		}
		expand_redir (cmd);
		cmd = cmd->next;
	}
}
