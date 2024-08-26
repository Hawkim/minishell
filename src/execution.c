/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:19:30 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/23 13:38:38 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void redirect_file_descriptors(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO); // Redirect input
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO); // Redirect output
		close(output_fd);
	}
}

void execute_command(const char *command, int input_fd, int output_fd, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_split(command, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		fprintf(stderr, "Error: Command not found: %s\n", cmd[0]);
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
		exit(EXIT_FAILURE);
	}
	redirect_file_descriptors(input_fd, output_fd);
	if (execve(path, cmd, envp) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void child_process(TreeNode *tree, int input_fd, int output_fd, char **envp)
{
    int pipe_fd[2];

	if (input_fd == -1)
		input_fd = STDIN_FILENO;
    // Base case: if tree is NULL, just return
    if (tree == NULL)
        return;

    if (ft_strncmp(tree->value, "|", 1) == 0)
    {
        // Handle the pipe symbol by setting up a pipe and processing left and right children
        if (pipe(pipe_fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        // Process the left child
        if (tree->left != NULL)
        {
            pid_t left_pid = fork();
            if (left_pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (left_pid == 0)
            {
                // In the left child process
                close(pipe_fd[0]); // Close the read end of the pipe
                if (input_fd != STDIN_FILENO)
                {
                    dup2(input_fd, STDIN_FILENO); // Redirect input from file or previous pipe
                    close(input_fd);
                }
                dup2(pipe_fd[1], STDOUT_FILENO); // Redirect output to the pipe
                close(pipe_fd[1]); // Close the write end of the pipe
                child_process(tree->left, STDIN_FILENO, STDOUT_FILENO, envp);
                exit(EXIT_SUCCESS);
            }
            else
            {
                // In the parent process
                close(pipe_fd[1]); // Close the write end of the pipe
                // Recursively process the right child
                child_process(tree->right, pipe_fd[0], output_fd, envp);
                waitpid(left_pid, NULL, 0); // Wait for left child to finish
            }
        }
    }
    else
    {
        // If the node's value is not a pipe symbol, execute the command
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // In the child process
            if (input_fd != STDIN_FILENO)
            {
                dup2(input_fd, STDIN_FILENO); // Redirect input from file or previous pipe
                close(input_fd);
            }
            if (output_fd != STDOUT_FILENO)
            {
                dup2(output_fd, STDOUT_FILENO); // Redirect output to file or pipe
                close(output_fd);
            }
            execute_command(tree->value, STDIN_FILENO, STDOUT_FILENO, envp);
            exit(EXIT_SUCCESS);
        }
        else
        {
            // In the parent process
            waitpid(pid, NULL, 0); // Wait for the child process to finish
        }
    }
}