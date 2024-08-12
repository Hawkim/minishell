/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:51:05 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/12 10:06:55 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		k;

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

// int main(int argc, char **argv, char **envp)
// {
//     // if (argc != 2) {
//     //     fprintf(stderr, "Usage: %s <VARIABLE_NAME>\n", argv[0]);
//     //     return EXIT_FAILURE;
//     // }
// 	(void)argc;
// 	(void)argv;
//     char *var = "$PATH";
//     char *def;
// 	def = search_env(var, envp);
//     if (def)
// 	{
//         printf("Definition of %s: %s\n", var, def);
//         free(def); // Free the allocated memory for the definition
//     }
// 	else
//         printf("Variable %s not found.\n", var);
//     return EXIT_SUCCESS;
// }