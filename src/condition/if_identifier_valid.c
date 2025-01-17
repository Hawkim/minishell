/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_identifier_valid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:20:05 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 12:20:04 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//  It contains a list of invalid
//characters, character combinations or blanks for export names

int	if_identifier_valid(char *keyy, t_minishell *g_minishell)
{
	int	i;

	i = 0;
	while (keyy[i])
	{
		if (!ft_isalnum(keyy[i]) || keyy[i] == '-' || keyy[i] == '.'
			|| keyy[i] == '{' || keyy[i] == '}'
			|| keyy[i] == '*' || keyy[i] == '#' || keyy[i] == '@'
			|| keyy[i] == '!' || keyy[i] == '^' || keyy[i] == '~'
			|| keyy[i] == '\"' || keyy[i] == '|' || keyy[i] == '$'
			|| keyy[i] == '\'' || keyy[i] == ';' || keyy[i] == '&'
			|| keyy[i] == '=' || keyy[i] == ' ')
		{
			g_minishell->exit_code = 1;
			return (0);
		}
		if (keyy[i] == '+' && keyy[i + 1] != '=')
		{
			g_minishell->exit_code = 1;
			return (0);
		}
		i++;
	}
	return (1);
}
