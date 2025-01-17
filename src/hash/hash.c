/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:55:22 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 13:17:21 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//The DJB2 algorithm is known for its simplicity and good distribution
//properties,
//making it suitable for hash table implementations. 
//The modulo operation at the end helps in mapping the
//hash value to an index within the bounds of the hash table size.

unsigned long int	hash_function(char *keyy, unsigned int size)
{
	unsigned long int	hash;
	unsigned int		i;

	hash = 5381;
	i = 0;
	while (keyy && keyy[i])
	{
		hash = ((hash << 5) + hash) + keyy[i];
		i++;
	}
	return (hash % size);
}

void	make_hashes(char keyy_w[], char value_w[], t_minishell *g_minishell)
{
	char	*keyy;
	char	*value;

	keyy = ft_strdup(keyy_w);
	value = ft_strdup(value_w);
	insert_hash(keyy, value, GLOBAL, g_minishell);
}

// Takes the list of env variable inserts them into the hash table
// varaibes : The list of environment variables

static char	*update_shlvl(void)
{
	int		num;
	char	*value;

	num = ft_atoi(getenv("SHLVL"));
	num++;
	value = ft_itoa(num);
	return (value);
}

void	send_to_hashtable(char **variables, t_minishell *g_minishell)
{
	char	*keyy;
	char	*value;
	int		i;

	i = 0;
	while (variables[i])
	{
		keyy = get_keyy(variables[i]);
		if (!ft_strncmp(keyy, "SHLVL", 5))
			value = update_shlvl();
		else
			value = get_value(variables[i]);
		insert_hash(keyy, value, GLOBAL, g_minishell);
		i++;
	}
	make_hashes("UID", "1000", g_minishell);
	if (!keyy_search("OLDPWD", g_minishell))
	{
		keyy = ft_strdup("OLDPWD");
		value = NULL;
		insert_hash(keyy, value, GLOBAL, g_minishell);
	}
}

//allocate memory for hashtable
//initiate value
//return table

t_hashtable	*init_hastable(char *env_str, t_minishell *g_minishell)
{
	t_hashtable	*table;
	int			i;

	i = 0;
	while (env_str[i])
		i++;
	table = malloc(sizeof(t_hashtable));
	if (!table)
	{
		free_shell(g_minishell);
		exit (12);
	}
	table->size = i + 1;
	table->count = 0;
	table->list = ft_calloc(sizeof(t_hashpair *), i + 1);
	if (!table->list)
	{
		free_shell(g_minishell);
		exit (12);
	}
	return (table);
}
// free_shell(g_minishell);
