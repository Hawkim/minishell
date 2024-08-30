#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

#include "../inc/minishell.h"

char	*get_heredoc_file_in(t_linkedlist_node *token_list)
{
	char	*filename;
	
	filename = NULL;
	if (token_list == NULL)
		return (NULL);
	while (token_list != NULL && token_list->next != NULL)
	{
		if (ft_strncmp(token_list->data, "<", 1) == 0
				&& ft_strncmp(token_list->next->data, "<", 1) == 0
				&& token_list->next->next != NULL)
			{
			filename = token_list->next->next->data;
			break;
			}
		token_list = token_list->next;
	}
	return (filename);
}

void print_file_content(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return;
	}
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;

	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		write(STDOUT_FILENO, buffer, bytes_read);
	}
	if (bytes_read < 0)
		perror("read");
	close(fd);
}

// void    open_heredoc_one(t_linkedlist_node *tokens)
// {
// 	const char *temp_filename = get_heredoc_file_in(tokens);
// 	char *new;
// 	int fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		exit(EXIT_FAILURE);
// 	}
// 	char *line = NULL;
// 	size_t len = 0;
// 	while (1)
// 	{
// 		ssize_t read = getline(&line, &len, stdin);
// 		if (read == -1)
// 		{
// 			perror("getline");
// 			break;
// 		}
// 		new = ft_strjoin(temp_filename, "\n");
// 		if (strcmp(line, new) == 0)
// 			break;
// 		write(fd, line, read);
// 	}
// 	free(line);
// 	close(fd);
// 	print_file_content(temp_filename);
// 	unlink(temp_filename);
// }

bool	is_cat(t_linkedlist_node *token_list)
{
	t_linkedlist_node	*current;

	current = token_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->data, "cat", 3) == 0)
			return (true);
		current = current->next;
	}
	return (false);
	
}

void open_heredoc_one(t_linkedlist_node *tokens)
{
	char *line;
    const char *temp_filename;
	const char	*temp2;
	int fd;
	int fd2;
	bool	file_exist;
	struct stat	buffer;

	temp_filename = get_heredoc_file_in(tokens);
	temp2 = ft_strjoin(get_heredoc_file_in(tokens), "_demo");
	if (stat(temp_filename, &buffer) == 0)
		file_exist = true;
    fd = open(temp_filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	fd2 = open(temp2, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    line = NULL;
    while (1)
    {
        line = readline("heredoc>"); // Read a line from stdin
        if (line == NULL)
        {
            perror("readline");
            break;
        }
        if (strcmp(line, temp_filename) == 0)
        {
            free(line);
            break;
        }
		if (!file_exist)
		{
        	write(fd, line, strlen(line)); // Write the line to the file
       	 write(fd, "\n", 1);
		}
		if (file_exist && is_cat(tokens))
		{
        	write(fd2, line, strlen(line)); // Write the line to the file
       	 write(fd2, "\n", 1);
		} // Add newline to the file
        free(line);
    }
    close(fd);
	close(fd2);
	if (is_cat(tokens))
    	print_file_content(temp2);//comment out i do not want to print the file into the terminal
	if (!file_exist && is_cat(tokens))
	{
		print_file_content(temp_filename);
		unlink(temp2);
		unlink(temp_filename);
	}
	if (!file_exist && !is_cat(tokens)){
		unlink(temp_filename);
    	unlink(temp2);}
	if (file_exist)
		unlink(temp2);
}

// int main()
// {
// 	char *input = "<< out";
// 	t_linkedlist_node *tokens = ftlexer(input);
// 	open_heredoc_one(tokens);
// 	return 0;
// }
