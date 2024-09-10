/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:08:54 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/10 11:09:40 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct node
{
	struct node	*next;
	char		*data;
}	t_env;

t_env	*free_env(t_env *head, t_env *current)
{
	while (head)
	{
		current = head;
		head = head ->next;
		free(current->data);
		free(current);
	}
	return (NULL);
}

t_env	*create_env(char **env)
{
	int		i;
	t_env	*head;
	t_env	*current;
	t_env	*prev;

	i = 0;
	head = NULL;
	current = NULL;
	prev = NULL;
	if (env == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		current = (t_env *)malloc(sizeof(t_env));
		if (current == NULL)
			return (free_env(head, current));
		current->data = strdup(env[i]);
		if (current->data == NULL)
			return (free_env(head, current));
		current->next = NULL;
		if (prev == NULL)
			head = current;
		else
			prev->next = current;
		prev = current;
		i++;
	}
	return (head);
}

void	print_env_list(t_env *head) {
    t_env *current = head;
    while (current != NULL) {
        printf("env : %s\n", current->data);
        current = current->next;
    }
}

int main(int argc, char *argv[], char **env) {
    // Example environment variables to test with
    char *sample_env[] = {
        "PATH=/usr/bin",
        "HOME=/home/user",
        "SHELL=/bin/bash",
        "LANG=en_US.UTF-8",
        NULL // Null-terminated array
    };

    // Create linked list from environment array
    t_env *env_list = create_env(env);

    // Print the linked list
    printf("Environment variables:\n");
    print_env_list(env_list);

    // Free the linked list
    free_env(env_list, NULL);

    return 0;
}
