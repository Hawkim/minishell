/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:54:04 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/26 14:19:52 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_heredoc_file(t_linkedlist_node *token_list)
{
	char	*filename;
	
	filename = NULL;
	if (token_list == NULL)
		return (NULL);
	while (token_list != NULL && token_list->next != NULL
			&& token_list->next->next != NULL)
	{
		if (ft_strncmp(token_list->data, ">", 1) == 0
				&& ft_strncmp(token_list->next->data, ">", 1) == 0)
			{
			filename = token_list->next->next->data;
			break;
			}
		token_list = token_list->next;
	}
	if (filename)
		return (filename);
	else
		return (NULL);
}

int open_heredoc_file(t_linkedlist_node *token_list)
{
	char	*filename;
	int		fd;
	
	filename = get_heredoc_file(token_list);
	if (filename == NULL) {
		return (-1);
		// fprintf(stderr, "Error: No output file specified\n");
		// exit(EXIT_FAILURE);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

char *get_heredoc_delimiter(t_linkedlist_node *token_list)
{
    char *delimiter;

	delimiter = NULL;
    while (token_list != NULL && token_list->next != NULL && token_list->next->next != NULL)
    {
        if (ft_strncmp(token_list->data, "<", 1) == 0
			&& ft_strncmp(token_list->next->data, "<", 1) == 0)
        {
            delimiter = token_list->next->next->data;
            break;
        }
        token_list = token_list->next;
    }

    return (delimiter);
}
