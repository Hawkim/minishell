/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_in_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:59:49 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// check if the current strin is between an even number of quotes
int	if_in_quotes(const char *input, size_t index)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = -1;
	while (i < (int)index)
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			if (in_quotes == -1)
				in_quotes = (int)i;
			else if (in_quotes != -1 && input[in_quotes] == input[i])
				in_quotes = -1;
		}
		i++;
	}
	if (in_quotes != -1)
		return (1);
	return (0);
}
