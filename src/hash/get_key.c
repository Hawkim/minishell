/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:14:48 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/03 18:21:11 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// get the key which is variable name 

char	*get_key(char *key_variable)
{
	char	*key;
	int		i;

	i = 0;
	if (!ft_strchr(key_variable, '=') || !key_variable)
		return (NULL);
	while (key_variable[i] != '=')
		i++; 
	key = malloc(sizeof(char) * (++i));
	ft_bzero(key, 0);
	if (!key)
		return (NULL);
	ft_strlcpy(key, key_variable, i);
	return (key);
}
