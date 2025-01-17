/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_command_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:05:50 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 11:51:22 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_command_valid(t_minishell *g_minishell)
{
	if (if_grammar_valid(g_minishell))
	{
		command_table(g_minishell);
		return (1);
	}
	return (0);
}
