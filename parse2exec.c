/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:50:28 by nal-haki          #+#    #+#             */
/*   Updated: 2024/08/12 13:21:37 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>

#define MAX_ARGS 128

void parse_and_execute(t_linkedlist_node *token_list) {
    char *args[MAX_ARGS];
    char *input_file = NULL;
    char *output_file = NULL;
    int append = 0;
    int pipe_fd[2];
    int has_pipe = 0;
    int arg_index = 0;
    int first_command = 1; // Flag to track the first command in the pipe chain

    t_linkedlist_node *node = token_list;

    while (node) {
        char *token = (char *)node->data;

        // Expand environment variables
        char *expanded_token = expand_env_vars(token);
        trim_trailing_spaces(expanded_token);

        if (strcmp(expanded_token, "|") == 0) {
            args[arg_index] = NULL;
            if (first_command) {
                // Set up pipe for the first command
                if (pipe(pipe_fd) == -1) {
                    perror("pipe failed");
                    exit(EXIT_FAILURE);
                }
                first_command = 0;
            } else {
                // Handle the case where there's a chain of pipes
                close(pipe_fd[1]); // Close previous pipe's write end
                if (pipe(pipe_fd) == -1) {
                    perror("pipe failed");
                    exit(EXIT_FAILURE);
                }
            }

            execute_command(args, input_file, output_file, append, pipe_fd, 1);
            arg_index = 0;
            input_file = NULL;
            output_file = NULL;
            append = 0;void parse_and_execute(t_linkedlist_node *token_list) {
    char *args[MAX_ARGS];
    char *input_file = NULL;
    char *output_file = NULL;
    int append = 0;
    int pipe_fd[2];
    int has_pipe = 0;
    int arg_index = 0;
    int first_command = 1; // Flag to track the first command in the pipe chain
    int previous_pipe_fd[2] = {-1, -1}; // To store file descriptors of the previous pipe

    t_linkedlist_node *node = token_list;

    while (node) {
        char *token = (char *)node->data;

        // Expand environment variables
        char *expanded_token = expand_env_vars(token);
        trim_trailing_spaces(expanded_token);

        if (strcmp(expanded_token, "|") == 0) {
            args[arg_index] = NULL;

            if (first_command) {
                // Set up pipe for the first command
                if (pipe(pipe_fd) == -1) {
                    perror("pipe failed");
                    exit(EXIT_FAILURE);
                }
            } else {
                // Close the old pipe's write end
                close(previous_pipe_fd[1]);

                // Set up new pipe
                if (pipe(pipe_fd) == -1) {
                    perror("pipe failed");
                    exit(EXIT_FAILURE);
                }
            }

            // Execute the command with output redirected to the pipe
            execute_command(args, input_file, output_file, append, pipe_fd, 1);

            // Close the new pipe's read end after forking
            close(pipe_fd[1]);

            // Save the new pipe's read end to be used by the next command
            previous_pipe_fd[0] = pipe_fd[0];
            previous_pipe_fd[1] = pipe_fd[1];

            // Reset for the next command
            arg_index = 0;
            input_file = NULL;
            output_file = NULL;
            append = 0;
            has_pipe = 1;
            first_command = 0;

        } else if (strcmp(expanded_token, ">") == 0) {
            node = node->next;
            if (node) {
                output_file = expand_env_vars((char *)node->data);
                trim_trailing_spaces(output_file);
            }
            append = 0;

        } else if (strcmp(expanded_token, ">>") == 0) {
            node = node->next;
            if (node) {
                output_file = expand_env_vars((char *)node->data);
                trim_trailing_spaces(output_file);
            }
            append = 1;

        } else if (strcmp(expanded_token, "<") == 0) {
            node = node->next;
            if (node) {
                input_file = expand_env_vars((char *)node->data);
                trim_trailing_spaces(input_file);
            }

        } else if (strcmp(expanded_token, "cd") == 0) {
            // Change directory command
            node = node->next;
            if (node) {
                char *path = expand_env_vars((char *)node->data);
                trim_trailing_spaces(path);
                if (chdir(path) != 0) {
                    perror("cd failed");
                }
                free(path);
            }

        } else {
            args[arg_index++] = expanded_token;
        }

        node = node->next;
    }

    args[arg_index] = NULL;

    // Execute the last command
    if (args[0] && strcmp(args[0], "cd") != 0) {
        if (has_pipe) {
            // Use the read end of the previous pipe for the last command's input
            dup2(previous_pipe_fd[0], STDIN_FILENO);
            close(previous_pipe_fd[0]);
        }
        execute_command(args, input_file, output_file, append, pipe_fd, 0);
    }

    // Close any remaining pipe file descriptors
    if (has_pipe) {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }

    // Wait for all child processes to finish
    while (wait(NULL) > 0);

    // Free dynamically allocated memory
    for (int i = 0; i < arg_index; i++) {
        free(args[i]);
    }
    if (input_file) free(input_file);
    if (output_file) free(output_file);
}


        } else if (strcmp(expanded_token, ">") == 0) {
            node = node->next;
            if (node) {
                output_file = expand_env_vars((char *)node->data);
                trim_trailing_spaces(output_file);
            }
            append = 0;
        } else if (strcmp(expanded_token, ">>") == 0) {
            node = node->next;
            if (node) {
                output_file = expand_env_vars((char *)node->data);
                trim_trailing_spaces(output_file);
            }
            append = 1;
        } else if (strcmp(expanded_token, "<") == 0) {
            node = node->next;
            if (node) {
                input_file = expand_env_vars((char *)node->data);
                trim_trailing_spaces(input_file);
            }
        } else if (strcmp(expanded_token, "cd") == 0) {
            // Change directory command
            node = node->next;
            if (node) {
                char *path = expand_env_vars((char *)node->data);
                trim_trailing_spaces(path);
                if (chdir(path) != 0) {
                    perror("cd failed");
                }
                free(path);
            }
        } else {
            args[arg_index++] = expanded_token;
        }

        node = node->next;
    }
    args[arg_index] = NULL;

    // Execute the last command
    if (args[0] && strcmp(args[0], "cd") != 0) {
        if (!first_command) {
            close(pipe_fd[1]);
        }
        execute_command(args, input_file, output_file, append, pipe_fd, 0);
    }

    // Close any open pipe file descriptors
    if (!first_command) {
        close(pipe_fd[0]);
    }

    // Wait for all child processes to complete
    while (wait(NULL) > 0);

    // Free dynamically allocated memory
    for (int i = 0; i < arg_index; i++) {
        free(args[i]);
    }
    if (input_file) free(input_file);
    if (output_file) free(output_file);
}
