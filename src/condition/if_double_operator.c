/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_double_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:58:15 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/13 17:09:12 by jabanna          ###   ########.fr       */
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
