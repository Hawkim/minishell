/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:10:44 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:02 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parser(void)
{
	start_tokenization();
	if (if_grammar_valid())
		return (0);
	command_table();
	return (1);
}

t_parser	*init_parser(void)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
	{
		free_minishell();
		exit(12);
	}
	parser->input = NULL;
	parser->tokens = NULL;
	return (parser);
}

// first initialize the global structure with the envp 
// parameter's list (converted into a hashtable)
// point all structures to NULL
void	init_shell(char **envp)
{
	char	*env_str;

	env_str = *envp;
	g_minishell.envp = init_hastable(env_str);
	send_to_hashtable(envp);
	g_minishell.parser = NULL;
	g_minishell.command = NULL;
	g_minishell.exit_code = 0;
}
