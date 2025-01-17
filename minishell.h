/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:14:48 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 13:28:20 by nal-haki         ###   ########.fr       */
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

typedef struct s_minishell1
{
	int			signal_code;
}	t_minishell1;
// global variable
extern t_minishell1	g_minishell1;
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
void				exe_builtin_parent(t_command *cmd,
						t_minishell *g_minishell);
void				exe_builtin_child(t_command *cmd, t_minishell *g_minishell);
int					ft_cd(char **exe, t_minishell *g_minishell);
int					ft_echo(char **exe);
int					ft_env(t_command *cmd, t_minishell *g_minishell);
int					ft_exit(char **exe, t_minishell *g_minishell);
int					ft_export(char **exe, t_minishell *g_minishell);
int					ft_pwd(char **exe, t_minishell *g_minishell);
int					ft_unset(char **exe, t_minishell *g_minishell);
void				check_env(char *keyy, char *value,
						t_minishell *g_minishell);
void				sub_hash(char *keyy, char *value,
						t_minishell *g_minishell);
void				export_hash(char *keyy, int new_attribute,
						t_minishell *g_minishell);
void				print_declarex(t_hashpair *node);
void				check_input(char **exe, t_minishell *g_minishell);
int					get_location(char *location_keyy, t_minishell *g_minishell);

// cmd
void				command_table(t_minishell *g_minishell);
void				add_cmd_back(t_command *cmd, t_minishell *g_minishell);
void				set_cmd_endp(t_command **cmd, t_token **list, int *prev,
						t_minishell **g_minishell);
t_command			*cmd_create(int id, t_minishell *g_minishell);

// exeution//
void				create_exe_envp(t_command *cmd, t_minishell *g_minishell);
void				close_fd(t_command *cmd, int fd_type);
void				exe_commands(t_command **cmd, t_minishell *g_minishell);
void				start_exeution(t_minishell *g_minishell);
void				close_all_fds(t_minishell *g_minishell);
//void    dup2_close_all_fds (t_command *command);
void				exe_child(t_command *cmd, t_minishell *g_minishell);

//hash//
void				bk_hash(t_hashpair **list, char *keyy,
						char *value, int atr);
void				insert_hash(char *keyy, char *value, int attribute,
						t_minishell *g_minishell);
void				send_to_hashtable(char **variables,
						t_minishell *g_minishell);
t_hashtable			*init_hastable(char *env_str, t_minishell *g_minishell);
char				*keyy_search(char *keyy, t_minishell *g_minishell);

//  expansion//
char				*replacement_expansion(t_token *token, int *index,
						t_minishell *g_minishell);
char				**split_variable_expansion(char	*expansion);
char				**parameter_expansion(t_token *token, int *index,
						t_minishell *g_minishell);
//char	*expand_variabe (t_token *token, int *index);
int					start_d_quote_expansion(t_token *to, int s, int *si,
						t_minishell *g_minishell);
int					start_s_quote_expansion(t_token *to, int s, int *si,
						t_minishell *g_minishell);
void				expand_d_quotes(t_token **token, int *i,
						t_minishell *g_minishell, int q);
void				expand_s_quotes(t_token **token, int *i,
						t_minishell *g_minishell, int q);
void				expand_param(t_token **token, int *index, int i,
						t_minishell *g_minishell);
void				expand_redir(t_command *cmd, t_minishell *g_minishell);
void				expand_token(t_token **token, t_minishell *g_minishell);
void				expand_cmd(t_minishell *g_minishell);
char				*expansion_array(int *ex, int i, int *size, t_token **tk);
void				free_lines(char	*ret, char *prev, char *next, char *ex);
char				*return_trim_token(char *token, char quote, int i);
int					count_chars_in_quote(char *token, int start, char quote);
//heredoc//
int					heredoc(char *name, t_minishell *g_minishell);

//token//
t_token				*create_token(char *token_value, int flag,
						t_minishell *g_minishell);
void				add_back_tkn(t_token **list, t_token *new_token);
void				add_to_token_list(const char *input, size_t size,
						t_minishell *g_minishell);
int					start_tokenization(t_minishell *g_minishell);

//token utils//
t_token				*token_dup(t_token *src, t_minishell *g_minishell);

//PATH//
char				**create_path_list(t_minishell *g_minishell);
void				check_path(t_command *cmd, char **path_list, char **path);
char				*setup_path(t_command *cmd, t_minishell *g_minishell);
char				*get_cmd_path(t_command *cmd, t_minishell *g_minishell);

//PID//
void				wait_pid(int pid[MAX_PID], int id,
						t_minishell *g_minishell);
void				check_pid(t_command **cmd, pid_t pid[MAX_PID], int id,
						t_minishell *g_minishell);

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
void				get_fileno(int redir_type, char *filename, t_command *cmd,
						t_minishell *g_minishell);
int					check_fds(t_command *cmd, t_minishell *g_minishell);
int					define_redir(t_minishell *g_minishell);
int					define_type_of_token(char *token);

//error//
int					heredoc_error(int *fd, t_minishell *g_minishell);
void				cmd_error(t_command *cmd, int nb, t_minishell *g_minishell);
void				return_error(char *filename, int error_number,
						t_minishell *g_minishell);
void				print_error(char *src, char *elem, char *str);
int					exit_num_error(char **exe);
int					args_error(t_minishell *g_minishell);

//free//
void				free_global(void);
void				free_shell(t_minishell *g_minishell);
void				free_path(char **path);
void				free_envp(t_command *cmd);
void				free_expansion(char **str, char *next);
void				free_exe_list(char **exe);
void				free_command(t_minishell *g_minishell);
void				free_tokens(t_token **tokens);
void				free_parser(t_minishell *g_minishell);
void				free_hashtable(t_minishell *g_minishell);
void				free_export(char **export);
void				free_node(t_hashpair *curr);

//pipe
void				open_pipes(t_minishell *g_minishell);
void				write_to_pipe(char *limiter, int *fd);

//what if//
int					if_redir(int prev, int type_of_token);//
int					if_builtin(t_command *cmd);//
int					if_fork_needed(t_command *cmd, t_minishell *g_minishell);//
int					if_expandable(char curr_char);//
int					if_quotes_valid(t_token *token);//
int					if_redir_valid(t_token *token, t_minishell *g_minishell);//
int					if_pipe_valid(t_token *token, int pos,
						t_minishell *g_minishell);//
int					if_command_valid(t_minishell *g_minishell);//
int					if_grammar_valid(t_minishell *g_minishell);//
int					if_in_quotes(const char *input, size_t index);//
int					if_double_operator(char curr, char prev);//
int					if_token_valid(const char *input, size_t i, size_t prev);//
int					if_identifier_valid(char *keyy, t_minishell *g_minishell);//
int					if_no_meta(char *keyy);
int					if_num_first(char *keyy);
int					if_option(char *keyy);
//WYSIWYG//
char				*get_value(char *variable);
char				*get_keyy(char *variable);
char				*get_pwd(void);
char				*get_folder_path(void);
//	INIT	//
t_parser			*init_parser(t_minishell *g_minishell);
void				init_shell(char **envp, t_minishell *g_minishell);
int					in_en(char *keyy, t_minishell *g_minishell);
char				*ft_clean(char *keyy, char c, char d);
#endif // !MINISHELL
