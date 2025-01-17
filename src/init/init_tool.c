/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:10:44 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 12:03:25 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parser(t_minishell *g_minishell)
{
	start_tokenization(g_minishell);
	if (if_grammar_valid(g_minishell))
		return (0);
	command_table(g_minishell);
	return (1);
}

t_parser	*init_parser(t_minishell *g_minishell)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
	{
		free_shell(g_minishell);
		exit(12);
	}
	parser->input = NULL;
	parser->tokens = NULL;
	return (parser);
}

// first initialize the global structure with the envp 
// parameter's list (converted into a hashtable)
// point all structures to NULL
void	init_shell(char **envp, t_minishell *g_minishell)
{
	char	*env_str;

	env_str = *envp;
	g_minishell->envp = init_hastable(env_str, g_minishell);
	send_to_hashtable(envp, g_minishell);
	g_minishell->parser = NULL;
	g_minishell->command = NULL;
	g_minishell->exit_code = 0;
}
