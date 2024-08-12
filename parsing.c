#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>

#define MAX_ARGS 128

// Function to expand environment variables
char *expand_env_vars(char *input) {
    char *result = malloc(strlen(input) + 1);
    char *ptr = result;
    char *env_var;
    char *env_val;
    int in_var = 0;

    while (*input) {
        if (*input == '$') {
            in_var = 1;
            input++;
            if (*input == '{') {
                input++;
                char var_name[128];
                char *var_ptr = var_name;
                while (*input && *input != '}' && var_ptr - var_name < sizeof(var_name) - 1) {
                    *var_ptr++ = *input++;
                }
                *var_ptr = '\0';
                if (*input == '}') input++; // Skip closing brace
                env_var = var_name;
            } else {
                char var_name[128];
                char *var_ptr = var_name;
                while (*input && !isspace(*input) && *input != '$' && var_ptr - var_name < sizeof(var_name) - 1) {
                    *var_ptr++ = *input++;
                }
                *var_ptr = '\0';
                env_var = var_name;
            }
            env_val = getenv(env_var);
            if (env_val) {
                strcpy(ptr, env_val);
                ptr += strlen(env_val);
            }
        } else {
            *ptr++ = *input++;
        }
    }
    *ptr = '\0';
    return result;
}

// Function to trim trailing newlines and spaces
void trim_trailing_spaces(char *str) {
    char *end = str + strlen(str) - 1;
    while (end >= str && isspace((unsigned char)*end)) {
        *end-- = '\0';
    }
}
void execute_command(char **args, char *input_file, char *output_file, int append, int pipe_fd[2], int has_pipe) {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        // Handle input redirection
        if (input_file) {
            int fd_in = open(input_file, O_RDONLY);
            if (fd_in < 0) { perror("open input file"); exit(EXIT_FAILURE); }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        // Handle output redirection
        if (output_file) {
            int fd_out = open(output_file, O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0644);
            if (fd_out < 0) { perror("open output file"); exit(EXIT_FAILURE); }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }

        // Handle piping
        if (has_pipe) {
            close(pipe_fd[0]); // Close unused read end
            dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
            close(pipe_fd[1]); // Close the write end
        }

        // Execute the command
        if (execvp(args[0], args) == -1) {
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) { // Parent process
        if (has_pipe) {
            close(pipe_fd[1]); // Close write end of the pipe
        }
        wait(NULL); // Wait for child process to finish
    } else {
        perror("fork failed");
    }
}
