/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:15:44 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/21 09:56:38 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct command {
	char			**args;
	struct command	*next;
}	t_command;

t_command	*parse_pipeline(t_linkedlist_node *token_list)
{
	t_command *head = NULL;
	t_command *current = NULL;

	while (token_list != NULL)
	{
		if (strcmp(token_list->data, "|") == 0) {
			// Finalize the current command and prepare for the next
			if (current) {
				current->next = malloc(sizeof(t_command));
				current = current->next;
				current->args = NULL; // Initialize for the next command
			}
		} else {
			// Add token to the current command's args
			// (Assuming a function to add args to the command)
			add_arg_to_command(current, token_list->data);
		}
		token_list = token_list->next; // Move to the next token
	}
	return head; // Return the head of the command list
}
