/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:21:27 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 14:10:29 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <strings.h>

// if expandable, will expand and find the substitution
// If '$' is followed by  '?',
// responds with the last exit status of the last command exeuted
// If '$' is followed by digit or an invalid name, no response
// If '$' is followed by valid name,
// responds with the value of the environment variable by 
// searching for it in the hashtable (cmd _table)
// free expansion at the end
char	**parameter_expansion(t_token *token, int *index)
{
	char	*expansion;
	char	*keyy;
	int		i;

	i = 0;
	if (token->token_value[*index] == '?')
		expansion = ft_itoa(g_minishell.exit_code);
	else if (ft_isdigit(token->token_value[*index]))
		expansion = NULL;
	else
	{
		while (ft_isalnum(token->token_value[(*index) + i])
			|| token->token_value[(*index) + i] == '_')
			i++;
		keyy = ft_strndup (&token->token_value[*index], i--);
		expansion = ft_strdup(keyy_search(keyy));
		free(keyy);
	}
	(*index) = (*index) + 1 + (i);
	return (split_variable_expansion(expansion));
	if (expansion)
		free(expansion);
}

// find what needs to be the replacement for the expansion
// exit code or the environment variable
// If a digit follows the '$', it won't be expanded

char	*replacement_expansion(t_token *token, int *index)
{
	char	*expansion;
	char	*keyy;
	int		i;

	i = 0;
	if (token->token_value[*index] == '?')
		expansion = ft_itoa(g_minishell.exit_code);
	else if (ft_isdigit(token->token_value[*index]))
		expansion = NULL;
	else
	{
		while (ft_isalnum(token->token_value[(*index) + i]))
			i++;
		keyy = ft_strndup (&token->token_value[*index], i--);
		expansion = ft_strdup(keyy_search(keyy));
		free(keyy);
	}
	*index = (*index) + (i) + 1;
	return (expansion);
}

static char	*return_prev(t_token **token, int *i)
{
	char	*prev;

	if ((ft_strchr((*token)->token_value, '$')
			&& if_expandable((*token)->token_value[*i + 1]))
		|| !ft_strncmp((*token)->token_value, "$\"\"\0", 4))
		prev = NULL;
	else
		prev = ft_strndup((*token)->token_value, *i);
	return (prev);
}

void	expand_quotes(t_token **token, int *i, char quote, int size)
{
	char	*prev;
	char	*next;
	char	*expansion;
	char	*ret;
	int		exp_flag;

	exp_flag = 1;
	prev = return_prev(token, i);
	(*i)++;
	while ((*token)->token_value[*i + size]
		&& (*token)->token_value[*i + size] != quote)
	{
		if ((*token)->token_value[*i + size] == '$' && (quote == '\"'))
			exp_flag = start_quote_expansion(*token, *i, &size, quote);
		size++;
	}
	expansion = expansion_array(&exp_flag, *i, &size, token);
	ret = ft_strjoin(prev, expansion);
	next = ft_strdup(&(*token)->token_value[*i + size]);
	*i = ft_strlen(ret) - 1;
	free((*token)->token_value);
	(*token)->token_value = ft_strjoin(ret, next);
	free_lines(ret, prev, next, expansion);
}
