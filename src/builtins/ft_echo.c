/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 01:13:40 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/07 01:13:45 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

int	check_option(char *option)
{
	int	i;
	int	counter;

	i = 1;
	counter = ft_strlen(option);
	while (option[i] && option[i] == 'n')
		i++;
	if (counter == i)
		return (1);
	else
		return (0);
}

int	check_if_option(char *exec)
{
	if (exec[0] == '-')
	{
		if (check_option(exec))
			return (1);
		return (0);
	}
	return (0);
}

int	ft_echo(char **exec)
{
	int	n_flag;
	int	i;

	i = 1;
	n_flag = 0;
	while (exec && exec[i] && check_if_option(exec[i]))
	{
		n_flag++;
		i++;
	}
	while (exec && exec[i])
	{
		printf("%s", exec[i]);
		if (exec[i] && exec[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}