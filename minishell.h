/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:14:48 by nal-haki          #+#    #+#             */
/*   Updated: 2024/11/21 14:04:56 by nal-haki         ###   ########.fr       */
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

# define BLACK "\001\033[0;30m"

//token
typedef struct s_token
{
	char			*token_value;
	int				type_of_token;
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
	char				**exe;
	char				*exe_path;
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
	char				*hash_keyy;
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

// t_command *command -> the exeutor
typedef struct s_minishell
{
	t_hashtable	*envp;
	t_parser	*parser;
	t_command	*command;
	int			exit_code;
}	t_minishell;

// global variable
extern t_minishell	g_minishell;
// one global variable (including all variables in a different strcut)

enum	e_type_of_token
{
	WORD,
	REDIR_OUT,
	APPEND,
	REDIR_IN,
	HEREDOC,
	PIPE
};

enum e_type
{
	GLOBAL,
	LOCAL
};

enum e_fd_type
{
	IN,
	OUT,
	BOTH,
};

//hashes no-matter-where misaligned var//
unsigned long int	hash_function(char *keyy, unsigned int size);

// builtins //
void				exe_builtin_parent(t_command *cmd);
void				exe_builtin_child(t_command *cmd);
int					ft_cd(char **exe);
int					ft_echo(char **exe);
int					ft_env(t_command *cmd);
int					ft_exit(char **exe);
int					ft_export(char **exe);
int					ft_pwd(char **exe);
int					ft_unset(char **exe);
void				check_env(char *keyy, char *value);
void				sub_hash(char *keyy, char *value);
void				export_hash(char *keyy, int new_attribute);
void				print_declarex(t_hashpair *node);
void				check_input(char **exe);
int					get_location(char *location_keyy);

// cmd
void				command_table(void);
void				add_cmd_back(t_command *cmd);
void				set_cmd_endp(t_command **cmd, t_token **list, int *prev);
t_command			*cmd_create(int id);

// exeution//
void				create_exe_envp(t_command *cmd);
void				close_fd(t_command *cmd, int fd_type);
void				exe_commands(t_command **cmd);
void				start_exeution(void);
void				close_all_fds(void);
//void    dup2_close_all_fds (t_command *command);
void				exe_child(t_command *cmd);

//hash//
void				bk_hash(t_hashpair **list, char *keyy,
						char *value, int atr);
void				insert_hash(char *keyy, char *value, int attribute);
void				send_to_hashtable(char **variables);
t_hashtable			*init_hastable(char *env_str);
char				*keyy_search(char *keyy);

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
void				exe_commands_parent_signals(void);
void				exe_commands_child_signals(void);
void				heredoc_handler(int signal);

//define//
void				get_fileno(int redir_type, char *filename, t_command *cmd);
int					check_fds(t_command *cmd);
int					define_redir(void);
int					define_type_of_token(char *token);

//error//
int					heredoc_error(int *fd);
void				cmd_error(t_command *cmd, int nb);
void				return_error(char *filename, int error_number);
void				print_error(char *src, char *elem, char *str);
int					exit_num_error(char **exe);
int					args_error(void);

//free//
void				free_shell(void);
void				free_path(char **path);
void				free_envp(t_command *cmd);
void				free_expansion(char **str, char *next);
void				free_exe_list(char **exe);
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
int					if_redir(int prev, int type_of_token);//
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
int					if_token_valid(const char *input, size_t i, size_t prev);//
int					if_identifier_valid(char *keyy);//
int					if_no_meta(char *keyy);
int					if_num_first(char *keyy);
int					if_option(char *keyy);
//WYSIWYG//
char				*get_value(char *variable);
char				*get_keyy(char *variable);
char				*get_pwd(void);
char				*get_folder_path(void);
//	INIT	//
t_parser			*init_parser(void);
void				init_shell(char **envp);
int					in_env_list(char *keyy);
char				*ft_clean(char *keyy, char c, char d);
#endif // !MINISHELL
