/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:07:54 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 11:56:54 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_parser(t_minishell *g_minishell)
{
	if (!g_minishell->parser)
		return ;
	if (g_minishell->parser->input)
		free(g_minishell->parser->input);
	if (g_minishell->parser->tokens)
		free_tokens(&g_minishell->parser->tokens);
	free(g_minishell->parser);
	g_minishell->parser = NULL;
}

void	free_shell(t_minishell *g_minishell)
{
	if (g_minishell->envp)
		free_hashtable(g_minishell);
	if (g_minishell->parser)
		free_parser(g_minishell);
	if (g_minishell->command)
		free_command(g_minishell);
	rl_clear_history();
}
