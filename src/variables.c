/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:51:05 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/19 14:11:11 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// #include "libft.h"

// typedef struct node
// {
// 	struct node	*next;
// 	char		*data;
// }	t_env;

// t_env	*free_env(t_env *head, t_env *current)
// {
// 	while (head)
// 	{
// 		current = head;
// 		head = head ->next;
// 		free(current->data);
// 		free(current);
// 	}
// 	return (NULL);
// }

// t_env	*create_env(char **env)
// {
// 	int		i;
// 	t_env	*head;
// 	t_env	*current;
// 	t_env	*prev;

// 	i = 0;
// 	head = NULL;
// 	current = NULL;
// 	prev = NULL;
// 	if (env == NULL)
// 		return (NULL);
// 	while (env[i] != NULL)
// 	{
// 		current = (t_env *)malloc(sizeof(t_env));
// 		if (current == NULL)
// 			return (free_env(head, current));
// 		current->data = ft_strdup(env[i]);
// 		if (current->data == NULL)
// 			return (free_env(head, current));
// 		current->next = NULL;
// 		if (prev == NULL)
// 			head = current;
// 		else
// 			prev->next = current;
// 		prev = current;
// 		i++;
// 	}
// 	return (head);
// }

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

// void	search_tokens(t_linkedlist_node *token_list, char **env)
// {
// 	t_linkedlist_node	*current;
// 	char				*def;

// 	current = token_list;
// 	while (current != NULL)
// 	{
// 		if (current->data[0] == '$' && (current->state != IN_SQUOTE))
// 		{
// 			def = search_env(current->data, env);
// 			if (def != NULL)
// 			{
// 				current->data = strdup(def);
// 				free(def);
// 			}
// 		}
// 		current = current->next;
// 	}
// }

// int main(int argc, char **argv, char **envp)
// {
//     // if (argc != 2) {
//     //     fprintf(stderr, "Usage: %s <VARIABLE_NAME>\n", argv[0]);
//     //     return EXIT_FAILURE;
//     // }
// 	(void)argc;
// 	(void)argv;
//     char *var = "$HOME";
// 	char input[] = "echo '\"'\"'\"Hello, | world!\"'\"'\"' > output.txt | grep \" \" $PATH hello\"'\"a ";
//     char *def;
// 	t_linkedlist_node *tokens = ftlexer(input, envp);
// 		printf("Tokens:\n");
// 	print_tokens(tokens);

// 	// char *d =  search_tokens(tokens, envp);
// 	// if (d)
// 	// {
// 	// 	printf("%s\n", d);
// 	// 	free(d);
// 	// }
// 	def = search_env(var, envp);
//     if (def)
// 	{
//         printf("Definition of %s: %s\n", var, def);
//         free(def); // Free the allocated memory for the definition
//     }
// 	else
//         printf("Variable %s not found.\n", var);
// 	// Free the linked list
// 	t_linkedlist_node *current = tokens;
// 	t_linkedlist_node *next;
// 	while (current != NULL) {
// 		next = current->next;
// 		free(current->data);
// 		free(current);
// 		current = next;
// 	}
//     return EXIT_SUCCESS;
// }