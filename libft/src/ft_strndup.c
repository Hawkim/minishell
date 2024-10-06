/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:56:16 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:04:39 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strndup(const char *s1, size_t size)
{
	char	*ptr;

	if (!size)
		return (NULL);
	ptr = (char *)malloc(sizeof(ptr) * size + 1);
	if (ptr == NULL)
		return (NULL);
	ptr = ft_memcpy(ptr, s1, size);
	ptr[size] = 0;
	return (ptr);
}
