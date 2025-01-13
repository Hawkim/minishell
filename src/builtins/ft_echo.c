/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 01:13:40 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/13 16:49:43 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pos(char *option)
{
	int	i;
	int	counter;

	i = 1;
	counter = ft_strlen(option);
	if (counter == 1)
		return (0);
	while (option[i] && option[i] == 'n')
		i++;
	if (counter == i)
		return (1);
	else
		return (0);
}

int	check_if_option(char *exe)
{
	if (exe[0] == '-')
	{
		if (check_pos(exe))
			return (1);
		return (0);
	}
	return (0);
}

int	ft_echo(char **exe)
{
	int	n_flag;
	int	i;

	i = 1;
	n_flag = 0;
	while (exe && exe[i] && check_if_option(exe[i]))
	{
		n_flag++;
		i++;
	}
	while (exe && exe[i])
	{
		printf("%s", exe[i]);
		// if (exe[i] && exe[i + 1] != NULL)
		// 	printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}
