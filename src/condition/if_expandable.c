/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_expandable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:17:10 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 13:28:20 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// check current char is expandable
// yes if after '?' or a letter
// if followed by a digit -> won't produce an output && '$'
// also won't be treated as an ordinary character.

int	clean_count_size(char *keyy, char c, char d)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (keyy[i])
	{
		if (keyy[i] == c || keyy[i] == d)
			counter++;
		i++;
	}
	return (i - counter);
}

char	*ft_clean(char	*keyy, char c, char d)
{
	int		size;
	char	*new_str;
	int		i;
	int		k;

	i = 0;
	k = 0;
	size = clean_count_size(keyy, c, d);
	new_str = malloc(sizeof(char) * size + 1);
	if (!new_str)
		return (NULL);
	while (keyy[i])
	{
		if (keyy[i] != c && keyy[i] != d)
		{
			new_str[k] = keyy[i];
			k++;
		}
		i++;
	}
	new_str[k] = '\0';
	return (new_str);
}

int	in_en(char *keyy, t_minishell *g_minishell)
{
	t_hashtable	*table;
	t_hashpair	*tmp;
	int			i;
	char		*new_keyy;

	table = g_minishell->envp;
	new_keyy = ft_clean(keyy, '$', '\"');
	i = hash_function(new_keyy, table->size);
	tmp = table->list[i];
	while (tmp)
	{
		if (!ft_strncmp(tmp->hash_keyy, new_keyy, ft_strlen(new_keyy)))
		{
			free(new_keyy);
			return (1);
		}
		tmp = tmp->next;
	}
	free(new_keyy);
	return (0);
}

int	if_expandable(char curr_char)
{
	if (ft_isalnum(curr_char) || curr_char == '_' || curr_char == '?')
		return (1);
	return (0);
}
