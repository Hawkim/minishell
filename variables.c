/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:51:05 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/18 01:14:36 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_word(char *def, char **env, int i, int j)
{
	int	k;

	k = 0;
	while (env[i][j] != '\0')
		def[k++] = env[i][j++];
	def[k] = '\0';
	return (def);
}
