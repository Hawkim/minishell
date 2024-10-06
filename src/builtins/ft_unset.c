/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:14:46 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/01 18:37:14 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Removes a variable from the hashtable's correct hashlist
void	unset_hash(char *key)
{
	t_hashpair	*curr;
	t_hashpair	*prev;
	int			i;

	i = hash_function(key, g_minishell.envp->size);
	prev = NULL;
	curr = g_minishell.envp->list[i];
	while (curr)
	{
		if (!ft_strncmp(curr->hash_key, key, ft_strlen(key) + 1))
		{
			if (!prev)
				g_minishell.envp->list[i] = curr->next;
			else
				prev->next = curr->next;
			free_node(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

//Unsets a variable from the envp list
// unset [options] var
// do not deal with options so the arg should be only one
// >> unset var
// if more args passed it should throw error of too many args ?
int	ft_unset(char **exec)
{
	int	i;

	i = 0;
	while (exec[++i])
	{
		if (if_no_meta(exec[i]) || if_num_first(exec[i])
			|| exec[i] == NULL )
		{
			if (if_option(exec[i]))
			{
				print_error("unset:`", exec[i], "\': not an option.");
				return (2);
			}
			print_error("unset:`", exec[i], "\': not a valid identifier ");
			return (1);
		}
		else
			unset_hash(exec[i]);
	}
	return (0);
}