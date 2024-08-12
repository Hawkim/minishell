#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define INITIAL "INITIAL"
# define IN_QUOTE "IN_QUOTE"
# define IN_SQUOTE "IN_SQUOTE"
# define IN_ESCAPE "IN_ESCAPE"

# define MAX_ARGS 128

typedef struct ll_node
{
    struct ll_node    *next;
    char              *data;
    char              *state;
} t_linkedlist_node;

typedef struct s_command
{
    char    **args;           // Array of argument strings
    char    *input_file;      // Input redirection file (NULL if none)
    char    *output_file;     // Output redirection file (NULL if none)
    int     is_append;        // Flag to indicate append mode (1 for >>)
    int     pipe_to_next;     // Flag to indicate if piping to the next command (1 if yes)
} t_command;

// Lexer Functions
t_linkedlist_node    *ftlexer(char *s);
void                append(t_linkedlist_node **token_list, char *s);
void                print_tokens(t_linkedlist_node *list);
void                quote_state(char *current_token, t_linkedlist_node *token_list, char *s, char *state, int i);
void                append_clear(t_linkedlist_node *token_list, char *current_token);

// Command Parsing and Execution Functions
void                parse_and_execute(t_linkedlist_node *token_list);
void                execute_command(char **args, char *input_file, char *output_file, int append, int pipe_fd[2], int has_pipe);
// Add these lines to minishell.h

// Function to expand environment variables
char *expand_env_vars(char *input);

// Function to trim trailing newlines and spaces
void trim_trailing_spaces(char *str);


// Utility Functions
t_command            *init_command();
void                add_argument(t_command *command, char *arg);
void                free_command(t_command *command);
void                free_token_list(t_linkedlist_node *list);

#endif
