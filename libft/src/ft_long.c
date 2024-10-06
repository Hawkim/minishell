/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:22:29 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_long(char *str)
{
	int		i;
	int		neg;
	long	value;

	i = 0;
	value = 0;
	neg = 0;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		if (value > 922337203685477580 || (value == 922337203685477580
				&& ((!neg && str[i] - '0' > 7) || (neg && str[i] - '0' > 8))))
			return (0);
		value = (value * 10) + str[i++] - '0';
	}
	while (ft_space(str[i]))
		i++;
	return (str[i] == '\0');
}
