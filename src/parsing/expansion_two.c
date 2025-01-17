/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:21:27 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 13:19:23 by nal-haki         ###   ########.fr       */
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

void	expand_param(t_token **token, int *index, int i,
	t_minishell *g_minishell)
{
	char	*prev;
	char	*next;
	char	**e;
	t_token	*last;

	if (!if_expandable ((*token)->token_value[(*index) + 1]))
		return ;
	prev = ft_strndup ((*token)->token_value, (*index)++);
	e = parameter_expansion(*token, index, g_minishell);
	next = ft_strdup(&(*token)->token_value[*index]);
	last = (*token)->next;
	(*token)->next = NULL;
	free ((*token)->token_value);
	(*token)->token_value = ft_strjoin (prev, e[i]);
	while (e[0] && e[++i])
		add_back_tkn(token, create_token(ft_strdup(e[i]), 1, g_minishell));
	while ((*token)->next)
		(*token) = (*token)->next;
	free(prev);
	prev = (*token)->token_value;
	(*token)->token_value = ft_strjoin(prev, next);
	free(prev);
	(*index) = ft_strlen(e[i]) - 1;
	(*token)->next = last;
	free_expansion(e, next);
}
//e = expansion_split

// with the exception of "<<" 
// jump to the next token and
// expand any dollar sign and quotes in the token
void	expand_redir(t_command *cmd, t_minishell *g_minishell)
{
	t_token	*token;

	token = cmd->redirections;
	while (token)
	{
		if (ft_strncmp(token->token_value, "<<", 3))
		{
			token = token->next;
			expand_token(&token, g_minishell);
		}
		else
			token = token->next;
		token = token->next;
	}
}

//iterate through the char* string "token_value"
// if dollar sign, replace it expand parameter;
// if quote sign, treat it as a string & expand with expand quotes

void	expand_token(t_token **token, t_minishell *g_minishell)
{
	int	i;

	i = 0;
	while ((*token)->token_value[i])
	{
		if (!ft_strncmp ("$EMPTY", (*token)->token_value, 5))
			rl_on_new_line();
		if ((*token)->token_value[i] == '$')
			expand_param (token, &i, 0, g_minishell);
		else if ((*token)->token_value[i] == '\"')
			expand_d_quotes(token, &i, g_minishell, 0);
		else if ((*token)->token_value[i] == '\'')
			expand_s_quotes(token, &i, g_minishell, 0);
		i++;
	}
}

//change the nodes of the token list into shell's grammar
// variable expansion according to the environment
// and local variables (prompted by '$')
// quotation expansion
// upon open and closing quotation marks

void	expand_cmd(t_minishell *g_minishell)
{
	t_command	*cmd;
	t_token		*token;

	cmd = g_minishell->command;
	while (cmd)
	{
		token = cmd->commands;
		while (token)
		{
			expand_token(&token, g_minishell);
			token = token->next;
		}
		expand_redir (cmd, g_minishell);
		cmd = cmd->next;
	}
}
