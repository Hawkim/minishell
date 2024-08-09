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
        if (input_file) {
            int fd_in = open(input_file, O_RDONLY);
            if (fd_in < 0) { perror("open input file"); exit(EXIT_FAILURE); }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (output_file) {
            int fd_out = open(output_file, O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0644);
            if (fd_out < 0) { perror("open output file"); exit(EXIT_FAILURE); }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        if (has_pipe) {
            close(pipe_fd[0]);
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);
        }
        if (execvp(args[0], args) == -1) {
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) { // Parent process
        if (has_pipe) {
            close(pipe_fd[1]);
            wait(NULL);
        }
    } else {
        perror("fork failed");
    }
}

void parse_and_execute(t_linkedlist_node *token_list) {
    char *args[MAX_ARGS];
    char *input_file = NULL;
    char *output_file = NULL;
    int append = 0;
    int pipe_fd[2];
    int has_pipe = 0;
    int arg_index = 0;

    t_linkedlist_node *node = token_list;

    while (node) {
        char *token = (char *)node->data;

        // Expand environment variables
        char *expanded_token = expand_env_vars(token);
        trim_trailing_spaces(expanded_token);

        if (strcmp(expanded_token, "|") == 0) {
            args[arg_index] = NULL;
            if (pipe(pipe_fd) == -1) {
                perror("pipe failed");
                exit(EXIT_FAILURE);
            }
            execute_command(args, input_file, output_file, append, pipe_fd, has_pipe);

            if (has_pipe) {
                close(pipe_fd[1]);
            }
            has_pipe = 1;
            arg_index = 0;
            input_file = NULL;
            output_file = NULL;
            append = 0;

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
        } else {
            args[arg_index++] = expanded_token;
        }

        node = node->next;
    }
    args[arg_index] = NULL;

    if (args[0]) {
        execute_command(args, input_file, output_file, append, pipe_fd, has_pipe);
    }

    if (has_pipe) {
        close(pipe_fd[1]);
        wait(NULL);
    }

    // Free dynamically allocated memory
    for (int i = 0; i < arg_index; i++) {
        free(args[i]);
    }
    if (input_file) free(input_file);
    if (output_file) free(output_file);
}

int main() {
    char *input = NULL;
    size_t len = 0;

    while (1) {
        printf("minishell> ");
        getline(&input, &len, stdin);
        
        if (strcmp(input, "exit\n") == 0 || strcmp(input, "quit\n") == 0) {
            break;
        }

        t_linkedlist_node *tokens = ftlexer(input);
        parse_and_execute(tokens);

        // Free the token list as before
        // free_token_list(tokens);
    }

    free(input);
    return 0;
}