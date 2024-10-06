/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:14:48 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/05 01:38:52 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft/include/libft.h"
# define MAX_PID 1024

# define  BLACK "\001\033[0;30m"

//token
typedef struct s_token
{
	char			*token_value;
	int				token_type;
	struct s_token	*next;
}	t_token;

//original inout & tokens
typedef struct s_parser
{
	char		*input;
	t_token		*tokens;
}	t_parser;

typedef struct s_command
{
	t_token				*commands;
	t_token				*redirections;
	int					endpoint;
	int					is_piped;
	char				**exec;
	char				*exec_path;
	char				**envp;
	int					fd_in;
	int					fd_out;
	int					fd_pipe[2];
	int					error_number;
	char				*error_file;
	int					id;
	struct s_command	*next;
}	t_command;

typedef struct s_hashpair
{
	char				*hash_key;
	char				*hash_value;
	int					attribute;
	struct s_hashpair	*next;
}	t_hashpair;

typedef struct s_hashtable
{
	t_hashpair	**list;
	size_t		size;
	size_t		count;
}	t_hashtable;

// t_command *command -> the executor
typedef struct s_minishell
{
	t_hashtable	*envp;
	t_parser	*parser;
	t_command	*command;
	int			exit_code;
}	t_minishell;

// global variable
extern t_minishell	g_minishell;
// one global variable (including all variables in different strcut)

enum	e_token_type{
	WORD,
	REDIR_OUT,
	APPEND,
	REDIR_IN,
	HEREDOC,
	PIPE
};

enum e_type{
	GLOBAL,
	LOCAL
};

enum e_fd_type {
	IN,
	OUT,
	BOTH,
};

//hashes no-matter-where misaligned var//
unsigned long int	hash_function(char *key, unsigned int size);

// builtins //
void				exec_builtin_parent(t_command *cmd);
void				exec_builtin_child(t_command *cmd);
int					ft_cd(char **exec);
int					ft_echo(char **exec);
int					ft_env(t_command *cmd);
int					ft_exit(char **exec);
int					ft_export(char **exec);
int					ft_pwd(char **exec);
int					ft_unset(char **exec);
void				check_env(char *key, char *value);
void				sub_hash(char *key, char *value);
void				export_hash(char *key, int new_attribute);
void				print_declarex(t_hashpair *node);
void				check_input(char **exec);
int					get_location(char *location_key);

// cmd
void				command_table(void);
void				add_cmd_back(t_command *cmd);
void				set_cmd_endp(t_command **cmd, t_token **list, int *prev);
t_command			*cmd_create(int id);

// execution//
void				create_exec_envp(t_command *cmd);
void				close_fd(t_command *cmd, int fd_type);
void				exec_commands(t_command **cmd);
void				start_execution(void);
void				close_all_fds(void);
//void    dup2_close_all_fds (t_command *command);
void				exec_child(t_command *cmd);

//hash//
void				bk_hash(t_hashpair **list, char *key, char *value, int atr);
void				insert_hash(char *key, char *value, int attribute);
void				send_to_hashtable(char **variables);
t_hashtable			*init_hastable(char *env_str);
char				*key_search(char *key);

//  expansion//
char				*replacement_expansion(t_token *token, int *index);
char				**split_variable_expansion(char	*expansion);
char				**parameter_expansion(t_token *token, int *index);
//char	*expand_variabe (t_token *token, int *index);
int					start_quote_expansion(t_token *to, int s, int *si, char q);
void				expand_quotes(t_token **token, int *i, char quote, int q);
void				expand_param(t_token **token, int *index, int i);
void				expand_redir(t_command *cmd);
void				expand_token(t_token **token);
void				expand_cmd(void);
char				*expansion_array(int *ex, int i, int *size, t_token **tk);
void				free_lines(char	*ret, char *prev, char *next, char *ex);
char				*return_trim_token(char *token, char quote, int i);
int					count_chars_in_quote(char *token, int start, char quote);
//heredoc//
int					heredoc(char *name);

//token//
t_token				*create_token(char *token_value, int flag);
void				add_back_tkn(t_token **list, t_token *new_token);
void				add_to_token_list(const char *input, size_t size);
int					start_tokenization(void);

//token utils//
t_token				*token_dup(t_token *src);

//PATH//
char				**create_path_list(void);
void				check_path(t_command *cmd, char **path_list, char **path);
char				*setup_path(t_command *cmd);
char				*get_cmd_path(t_command *cmd);

//PID//
void				wait_pid(int pid[MAX_PID], int id);
void				check_pid(t_command **cmd, pid_t pid[MAX_PID], int id);

//SIGNALS//
void				interrupt_handler(int signal);
void				quit_handler(int signal);
void				main_loop_handler(int signal);
void				parent_handler(int signal);
void				change_signals(void);
void				get_heredoc_child_signal(void);
void				get_heredoc_parent_signal(void);
void				exec_commands_parent_signals(void);
void				exec_commands_child_signals(void);
void				heredoc_handler(int signal);

//define//
void				get_fileno(int redir_type, char *filename, t_command *cmd);
int					check_fds(t_command *cmd);
int					define_redir(void);
int					define_token_type(char *token);

//error//
int					heredoc_error(int *fd);
void				cmd_error(t_command *cmd, int nb);
void				return_error(char *filename, int error_number);
void				print_error(char *src, char *elem, char *str);
int					exit_num_error(char **exec);
int					args_error(void);

//free//
void				free_minishell(void);
void				free_path(char **path);
void				free_envp(t_command *cmd);
void				free_expansion(char **str, char *next);
void				free_exec_list(char **exec);
void				free_command(void);
void				free_tokens(t_token **tokens);
void				free_parser(void);
void				free_hashtable(void);
void				free_export(char **export);
void				free_node(t_hashpair *curr);

//pipe
void				open_pipes(void);
void				write_to_pipe(char *limiter, int *fd);

//what if//
int					if_redir(int prev, int token_type);//
int					if_builtin(t_command *cmd);//
int					if_fork_needed(t_command *cmd);//
int					if_expandable(char curr_char);//
int					if_quotes_valid(t_token *token);//
int					if_redir_valid(t_token *token);//
int					if_pipe_valid(t_token *token, int pos);//
int					if_command_valid(void);//
int					if_grammar_valid(void);//
int					if_in_quotes(const char *input, size_t index);//
int					if_double_operator(char curr, char prev);//
int					if_valid_token(const char *input, size_t i, size_t prev);//
int					if_identifier_valid(char *key);//
int					if_no_meta(char *key);
int					if_num_first(char *key);
int					if_option(char *key);
//WYSIWYG//
char				*get_value(char *variable);
char				*get_key(char *variable);
char				*get_pwd(void);
char				*get_folder_path(void);
//	INIT	//
t_parser			*init_parser(void);
void				init_shell(char **envp);
int					in_env_list(char *key);
char				*ft_clean(char *key, char c, char d);
#endif // !MINISHELL
