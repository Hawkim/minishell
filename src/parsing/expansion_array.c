/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:21:27 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:09 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expansion_array(int *exp_flag, int i, int *size, t_token **token)
{
	char	*expansion;

	expansion = NULL;
	if (!(*exp_flag))
		expansion = NULL;
	else if (*exp_flag && *size > 0)
		expansion = ft_strndup(&(*token)->token_value[i], *size);
	*exp_flag = 1;
	return (expansion);
}
