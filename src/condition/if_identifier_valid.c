/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_identifier_valid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:20:05 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/13 17:10:18 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//  It contains a list of invalid
//characters, character combinations or blanks for export names

int	if_identifier_valid(char *keyy)
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
			g_minishell.exit_code = 1;
			return (0);
		}
		if (keyy[i] == '+' && keyy[i + 1] != '=')
		{
			g_minishell.exit_code = 1;
			return (0);
		}
		i++;
	}
	return (1);
}
