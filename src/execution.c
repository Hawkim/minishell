/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:19:30 by jabanna           #+#    #+#             */
/*   Updated: 2024/09/01 00:07:59 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void redirect_file_descriptors(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
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
                // in the left child process
                close(pipe_fd[0]); // close the read end of the pipe
                if (input_fd != STDIN_FILENO)
                {
                    dup2(input_fd, STDIN_FILENO); // redirect input from file or previous pipe
                    close(input_fd);
                }
                dup2(pipe_fd[1], STDOUT_FILENO); // redirect output to the pipe
                close(pipe_fd[1]); // close the write end of the pipe
                child_process(tree->left, STDIN_FILENO, STDOUT_FILENO, envp);
                exit(EXIT_SUCCESS);
            }
            else
            {
                // in the parent process
                close(pipe_fd[1]); // close the write end of the pipe
                child_process(tree->right, pipe_fd[0], output_fd, envp); // the input is the read end of the pipe
                waitpid(left_pid, NULL, 0); // wait for left child to finish
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