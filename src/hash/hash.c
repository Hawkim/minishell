/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:55:22 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/27 17:13:53 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

unsigned long int	hash_function(char *key, unsigned int size)
{
	unsigned long int	hash;
	unsigned int		i;

	hash = 5381;
	i = 0;
	while (key && key[i])
	{
		hash = ((hash << 5) + hash) + key[i];
		i++;
	}
	return (hash % size);
}

void	make_hashes(char key_w[], char value_w[])
{
	char	*key;
	char	*value;

	key = ft_strdup(key_w);
	value = ft_strdup(value_w);
	insert_hash(key, value, GLOBAL);
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

void	send_to_hashtable(char **variables)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (variables[i])
	{
		key = get_key(variables[i]);
		if (!ft_strncmp(key, "SHLVL", 5))
			value = update_shlvl();
		else
			value = get_value(variables[i]);
		insert_hash(key, value, GLOBAL);
		i++;
	}
	make_hashes("UID", "1000");
	if (!key_search("OLDPWD"))
	{
		key = ft_strdup("OLDPWD");
		value = NULL;
		insert_hash(key, value, GLOBAL);
	}
}

//allocate memory for hashtable
//initiate value
//return table

t_hashtable	*init_hastable(char *env_str)
{
	t_hashtable	*table;
	int			i;

	i = 0;
	while (env_str[i])
		i++;
	table = malloc(sizeof(t_hashtable));
	if (!table)
	{
		free_minishell();
		exit (12);
	}
	table->size = i + 1;
	table->count = 0;
	table->list = ft_calloc(sizeof(t_hashpair *), i + 1);
	if (!table->list)
	{
		free_minishell();
		exit (12);
	}
	return (table);
}
