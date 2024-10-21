/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:21:16 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 14:10:29 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Substitute a new variable at the end of the hashtable's correct hashlist
void	sub_hash(char *keyy, char *value)
{
	t_hashtable	*table;
	t_hashpair	*list;
	char		*sub;
	int			i;

	table = g_minishell.envp;
	i = hash_function(keyy, table->size);
	list = table->list[i];
	while (ft_strncmp(list->hash_keyy, keyy, ft_strlen(keyy)))
		list = list->next;
	sub = list->hash_value;
	if (value)
		list->hash_value = ft_strdup(value);
	free(sub);
	free(keyy);
	free(value);
}

//Export a variable set locally to the enviroment
void	export_hash(char *keyy, int new_attribute)
{
	t_hashtable	*table;
	t_hashpair	*list;
	int			i;

	table = g_minishell.envp;
	i = hash_function (keyy, table->size);
	list = table->list[i];
	while (ft_strncmp(list->hash_keyy, keyy, ft_strlen(keyy)))
		list = list->next;
	list->attribute = new_attribute;
	free(keyy);
}

void	print_declarex(t_hashpair *node)
{
	if (!node->hash_value)
		printf("declare -x %s\n", node->hash_keyy);
	else
		printf("declare -x %s=\"%s\"\n",
			node->hash_keyy, node->hash_value);
}

// check if empty str args or no args
// print all env variable that are exported

void	check_input(char **exe)
{
	t_hashpair	**pair;
	t_hashpair	*node;
	size_t		i;

	if ((!exe[1] || !*exe[1]) && ft_strncmp(exe[1], "\0", 1))
	{
		i = 0;
		pair = g_minishell.envp->list;
		while (i < g_minishell.envp->size)
		{
			node = pair[i];
			while (node)
			{
				if (node->attribute == GLOBAL)
					print_declarex(node);
				node = node->next;
			}
			i++;
		}
	}
}

// Checks location where the variable is stored 
// Global table -> 0
// Local table -> 1
// not found -> -1
int	get_location(char *location_keyy)
{
	t_hashtable	*table;
	t_hashpair	*tmp;
	int			i;

	table = g_minishell.envp;
	i = hash_function(location_keyy, table->size);
	tmp = table->list[i];
	while (tmp)
	{
		if (!ft_strncmp(tmp->hash_keyy, location_keyy, ft_strlen(location_keyy)))
			return (tmp->attribute);
		tmp = tmp->next;
	}
	return (-1);
}
