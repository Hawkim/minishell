/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:15:27 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// get the value of the variable content 
char	*get_value(char *value_variable)
{
	char	*value;
	int		i;

	if (!ft_strchr(value_variable, '='))
		return (NULL);
	i = 0;
	while (value_variable[i] != '=')
		i++;
	value = ft_strdup(&value_variable[++i]);
	return (value);
}
