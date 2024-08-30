/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:42:11 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/29 11:21:17 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_heredoc_file(t_linkedlist_node *token_list)
{
	char	*filename;
	
	filename = NULL;
	if (token_list == NULL)
		return (NULL);
	while (token_list != NULL && token_list->next != NULL)
	{
		if (ft_strncmp(token_list->data, ">", 1) == 0
				&& ft_strncmp(token_list->next->data, ">", 1) != 0)
			{
			filename = token_list->next->data;
			break;
			}
		if (ft_strncmp(token_list->data, ">", 1) == 0
				&& ft_strncmp(token_list->next->data, ">", 1) == 0
				&& token_list->next->next != NULL)
			{
			filename = token_list->next->next->data;
			break;
			}
		token_list = token_list->next;
	}
	return (filename);
}

int open_heredoc_file(t_linkedlist_node *token_list)
{
	char	*filename;
	int		fd;
	
	filename = get_heredoc_file(token_list);
	if (filename == NULL) {
		printf("bash: syntax error near unexpected token `newline'");
		return (-1);
		// fprintf(stderr, "Error: No output file specified\n");
		// exit(EXIT_FAILURE);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
			// && ft_strncmp(token_list->next->next->data, ">", 1) != 0)
		{
			delimiter = token_list->next->next->data;
			break;
		}
		token_list = token_list->next;
	}

	return (delimiter);
}

// void heredoc_input(t_linkedlist_node *token_list)
// {
// 	char *delimiter = get_heredoc_delimiter(token_list);
// 	int fd;
// 	char buffer[1024];
// 	char temp_buffer[1024];
// 	ssize_t bytes_read;
	
// 	if (delimiter == NULL)
// 	{
// 		fprintf(stderr, "Error: No delimiter specified\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	fd = open_heredoc_file(token_list);
// 	if (fd == -1)
// 		exit(EXIT_FAILURE);
// 	printf("Enter input (type '%s' on a new line to end):\n", delimiter);
// 	while (1)
// 	{
// 		bytes_read = read(STDIN_FILENO, temp_buffer, sizeof(temp_buffer) - 1);
// 		if (bytes_read == -1)
// 		{
// 			perror("read");
// 			close(fd);
// 			exit(EXIT_FAILURE);
// 		}
// 		if (bytes_read == 0)
// 			// EOF reached
// 			break;
// 		temp_buffer[bytes_read] = '\0';  // Null-terminate the buffer
// 		// Check if the input contains the delimiter
// 		char *end_marker = strstr(temp_buffer, delimiter);
// 		if (end_marker != NULL)
// 		{
// 			// Write up to the delimiter and stop
// 			size_t delimiter_pos = end_marker - temp_buffer;
// 			if (write(fd, temp_buffer, delimiter_pos) == -1)
// 			{
// 				perror("write");
// 				close(fd);
// 				exit(EXIT_FAILURE);
// 			}
// 			break;
// 		}
// 		// Write the entire buffer to the file
// 		if (write(fd, temp_buffer, bytes_read) == -1)
// 		{
// 			perror("write");
// 			close(fd);
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	close(fd);
// 	printf("Input saved to file.\n");
// }

void validate_delimiter(const char *delimiter)
{
    if (delimiter == NULL || ft_strncmp(delimiter, ">", 1) == 0)
    {
        fprintf(stderr, "bash: syntax error near unexpected token `>>'\n");
        exit(EXIT_FAILURE);
    }
}

void write_line_to_fd(int fd, const char *line)
{
    if (write(fd, line, strlen(line)) == -1 || write(fd, "\n", 1) == -1)
    {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
}

void heredoc_input(t_linkedlist_node *token_list)
{
	char *delimiter; 
	int fd;
	char *line;
	size_t delimiter_len;

	delimiter = get_heredoc_delimiter(token_list);
	delimiter_len = ft_strlen(delimiter);
	validate_delimiter(delimiter);
	fd = open_heredoc_file(token_list);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break;
		if (ft_strncmp(line, delimiter, delimiter_len) == 0 && ft_strlen(line) == delimiter_len)
		{
			free(line);
			close(fd);
			return;
		}
		if (is_cat(token_list))
			write_line_to_fd(fd, line); //comment out if i want to add to the file that is created
		free(line);
	}
	close(fd);
}

// int main(int argc, char *argv[])
// {
// 	char *input = "cat << a >> b";
// 	t_linkedlist_node *tokens = ftlexer(input);
// 	heredoc_input(tokens);
// 	return 0;
// }
