/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:21:27 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 13:30:24 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// it trims the token inside quotes,
// and with the return str it searches in the hash list 
// holding the env variables
// if not found, then no expansion needed
// it shoud not return the "$NOTHING"
int	count_chars_in_quote(char *token, int start, char quote)
{
	int	i;

	i = 0;
	while (token[start + i])
	{
		if (token[start + i] == quote)
			return (i);
		i++;
	}
	return (i);
}

char	*return_trim_token(char *token, char quote, int i)
{
	int		in_quotes_size;
	char	*new_token;

	in_quotes_size = count_chars_in_quote(token, i, quote);
	new_token = ft_substr(token, i, in_quotes_size);
	return (new_token);
}

void	free_lines(char	*ret, char *prev, char *next, char *expansion)
{
	free(ret);
	free(prev);
	free(next);
	if (expansion)
		free(expansion);
}

int	start_d_quote_expansion(t_token *token, int start, int *size,
	t_minishell *g_minishell)
{
	char	*prev;
	char	*expansion;
	char	*next;
	int		i;
	char	*actual_token;

	i = start + (*size);
	if (token->token_value[i] == '$' && token->token_value[i + 1] == '\"'
		&& token->token_value[i - 1] == '\"')
		return (1);
	actual_token = return_trim_token(token->token_value, '\"', i);
	if (if_expandable(token->token_value[i + 1])
		|| in_en(actual_token, g_minishell) || token->token_value[i + 1] == '?')
	{
		prev = ft_strndup(token->token_value, i++);
		expansion = replacement_expansion(token, &i, g_minishell);
		next = ft_strdup(&token->token_value[i]);
		free(token->token_value);
		token->token_value = ft_strnjoin(3, prev, expansion, next);
		*size = (*size) + ft_strlen(expansion) - 2;
		free_lines(prev, next, actual_token, expansion);
		return (1);
	}
	free(actual_token);
	return (0);
}

int	start_s_quote_expansion(t_token *token, int start, int *size,
	t_minishell *g_minishell)
{
	char	*prev;
	char	*expansion;
	char	*next;
	int		i;
	char	*actual_token;

	i = start + (*size);
	if (token->token_value[i] == '$' && token->token_value[i + 1] == '\"'
		&& token->token_value[i - 1] == '\"')
		return (1);
	actual_token = return_trim_token(token->token_value, '\'', i);
	if (if_expandable(token->token_value[i + 1])
		|| in_en(actual_token, g_minishell) || token->token_value[i + 1] == '?')
	{
		prev = ft_strndup(token->token_value, i++);
		expansion = replacement_expansion(token, &i, g_minishell);
		next = ft_strdup(&token->token_value[i]);
		free(token->token_value);
		token->token_value = ft_strnjoin(3, prev, expansion, next);
		*size = (*size) + ft_strlen(expansion) - 2;
		free_lines(prev, next, actual_token, expansion);
		return (1);
	}
	free(actual_token);
	return (0);
}
//in_en = in_env_list;
