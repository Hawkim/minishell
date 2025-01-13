/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:21:16 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/13 17:22:38 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// check if the variable to export already exist in the env
// if yes -> replace the value
// if not -> add the value to the env 
// if the export is local, add to env
void	check_env(char *keyy, char *value)
{
	int	location;

	location = get_location(keyy);
	if (location == -1)
		insert_hash(keyy, value, GLOBAL);
	else if (location == GLOBAL && value)
		sub_hash(keyy, value);
	else if (location == LOCAL)
		export_hash(keyy, GLOBAL);
}

// Sets environment variables
// Environmental
// variables are exported in it as child processes
// The existing environment
// variables are not affected.
// If a variable already exists in the env list, substitute it
// If it exists in the local list,
// remove it from  local list and add it to the env
// If no operator "=" is
// found in the argument, nothing will be done but no error will be printed

static int	invalid_var_name(char *keyy)
{
	if (if_num_first(keyy) || ft_cap_num(keyy) || !ft_strncmp(keyy, "\0", 1))
		return (1);
	return (0);
}

static void	deal_values(char *value, char *exe, char *keyy)
{
	value = get_value(exe);
	check_env(keyy, value);
}

// static int	return_msg(char *keyy, int i, char *str)
// {
// 	print_error("export:`", keyy, str);
// 	free(keyy);
// }

int	ft_export(char **exe)
{
	char	*keyy;
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	check_input(exe);
	while (exe[++i])
	{
		keyy = get_keyy(exe[i]);
		if (!keyy || keyy[0] == '\0')
			keyy = ft_strdup(exe[i]);
		if (if_option(keyy) || invalid_var_name(keyy))
		{
			printf("%s: not a valid option.\n", keyy);
			free(keyy);
		}
		else
			deal_values(value, exe[i], keyy);
	}
	return (0);
}
