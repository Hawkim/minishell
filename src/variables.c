/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:51:05 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/29 23:50:15 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*fill_word(char *def, char **env, int i, int j)
{
	int	k;

	k = 0;
	while (env[i][j] != '\0')
		def[k++] = env[i][j++];
	def[k] = '\0';
	return (def);
}

char	*search_env(char *var, char **env)
{
	int		i;
	char	*def;
	int		var_len;
	int		j;
	// int		k;

	if (var == NULL)
		return (NULL);
	i = 0;
	var_len = strlen(var) - 1;
	while (env[i])
	{
		if (strncmp(env[i], var + 1, var_len) == 0 && env[i][var_len] == '=')
		{
			def = malloc(strlen(env[i]) - var_len);
			if (!def)
				exit(EXIT_FAILURE);
			j = var_len + 1;
			return (fill_word(def, env, i, j));
		}
		i++;
	}
	return (NULL);
}

void	search_tokens(t_linkedlist_node *token_list, char **env)
{
	t_linkedlist_node	*current;
	char				*def;

	current = token_list;
	while (current != NULL)
	{
		if ( current->data[0] == '$' && (strcmp(current->state, "IN_SQUOTE") == 0))
		{
			def = search_env(current->data, env);
			if (def != NULL)
			{
				current->data = strdup(def);
				free(def);
			}
		}
		current = current->next;
	}
}
