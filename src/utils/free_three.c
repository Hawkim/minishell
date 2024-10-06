/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:07:54 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/27 17:20:20 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_parser(void)
{
	if (!g_minishell.parser)
		return ;
	if (g_minishell.parser->input)
		free(g_minishell.parser->input);
	if (g_minishell.parser->tokens)
		free_tokens(&g_minishell.parser->tokens);
	free(g_minishell.parser);
	g_minishell.parser = NULL;
}

void	free_minishell(void)
{
	if (g_minishell.envp)
		free_hashtable();
	if (g_minishell.parser)
		free_parser();
	if (g_minishell.command)
		free_command();
	rl_clear_history();
}
