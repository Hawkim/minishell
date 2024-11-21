/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_no_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:20:05 by nal-haki          #+#    #+#             */
/*   Updated: 2024/11/09 05:16:47 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_option(char *keyy)
{
	if (keyy[0] == '-')
		return (1);
	return (0);
}

int	if_num_first(char *keyy)
{
	if (ft_isdigit(keyy[0]))
		return (1);
	return (0);
}

//if invalid but _ char is valid
//for unset and export variables
int	if_no_meta(char *keyy)
{
	int	i;

	i = 0;
	while (keyy[i])
	{
		if ((!ft_isalnum(keyy[i]) && keyy[i] != '_') || keyy[i] == '-'
			|| keyy[i] == '.' || keyy[i] == '{' || keyy[i] == '}'
			|| keyy[i] == '*' || keyy[i] == '#' || keyy[i] == '@'
			|| keyy[i] == '!' || keyy[i] == '^' || keyy[i] == '~'
			|| keyy[i] == '\"' || keyy[i] == '|' || keyy[i] == '$'
			|| keyy[i] == '\'' || keyy[i] == ';' || keyy[i] == '&'
			|| keyy[i] == '=' || keyy[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
