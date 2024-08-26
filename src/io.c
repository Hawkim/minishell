/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:10:37 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/23 14:20:09 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_filein(t_linkedlist_node *token_list)
{
	char	*filein;

	filein = NULL;
	if (token_list == NULL)
		return (NULL);
	while (token_list != NULL)
	{
		if (ft_strncmp(token_list->data, "<", 1) == 0)
			filein = token_list->next->data;
		token_list = token_list->next;
	}
	if (filein)
		return (filein);
	else
		return (NULL);
}

char	*get_fileout(t_linkedlist_node *token_list)
{
	char	*fileout;

	fileout = NULL;
	if (token_list == NULL)
		return (NULL);
	while (token_list != NULL)
	{
		if (ft_strncmp(token_list->data, ">", 1) == 0)
			fileout = token_list->next->data;
		token_list = token_list->next;
	}
	if (fileout)
		return (fileout);
	else
		return (NULL);
}

int open_input_file(t_linkedlist_node *token_list)
{
	char	*filename;
	int		fd;

	filename = get_filein(token_list);
	if (filename == NULL) {
		return (-1);
		// fprintf(stderr, "Error: No input file specified\n");
		// exit(EXIT_FAILURE);
	}

	// Open the file for reading only
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		// exit(EXIT_FAILURE);
	}
	return (fd);
}

int open_output_file(t_linkedlist_node *token_list)
{
	char	*filename;
	int		fd;
	
	filename = get_fileout(token_list);
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