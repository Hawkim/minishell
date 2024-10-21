/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_double_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:58:15 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//check if there are double symbol
int	if_double_operator(char curr, char prev)
{
	if (curr == '|' && prev == '|')
		return (0);
	if (curr == '>' && prev == '>')
		return (0);
	if (curr == '<' && prev == '<')
		return (0);
	if (curr == '&' && prev == '&')
		return (0);
	if (curr == ' ' && prev == ' ')
		return (0);
	return (1);
}
