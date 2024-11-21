/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_keyy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:14:48 by nal-haki          #+#    #+#             */
/*   Updated: 2024/11/21 13:56:27 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// get the keyy which is variable name 

char	*get_keyy(char *keyy_variable)
{
	char	*keyy;
	int		i;

	i = 0;
	if (!ft_strchr(keyy_variable, '=') || !keyy_variable)
		return (NULL);
	while (keyy_variable[i] != '=')
		i++;
	keyy = malloc(sizeof(char) * (++i));
	ft_bzero(keyy, 0);
	if (!keyy)
		return (NULL);
	ft_strlcpy(keyy, keyy_variable, i);
	return (keyy);
}
