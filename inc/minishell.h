/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:39:40 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/29 19:55:25 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <ctype.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/inc/libft.h"
# define INITIAL "INITIAL"
# define IN_QUOTE "IN_QUOTE"
# define IN_SQUOTE "IN_SQUOTE"

typedef struct ll_node
{
	struct ll_node	*next;
	char			*data;
	char			*state;
}	t_linkedlist_node;

typedef struct TreeNode
{
	char			*value; // Command or operator
	struct TreeNode	*left; // Left child (for commands)
	struct TreeNode	*right; // Right child (for pipes)
	struct TreeNode *parent;
} TreeNode;

t_linkedlist_node	*ftlexer(char *s);
// TreeNode* ftlexer(char *s, char **envp);
void				append(t_linkedlist_node **token_list, char *s);
void				print_tokens(t_linkedlist_node *list);
void				search_tokens(t_linkedlist_node *token_list, char **env);
char				*search_env(char *var, char **env);
char				*search_string(char *s, char **env);
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);
char				*find_path(char *cmd, char **envp);
void				execute(char *argv, char **envp);
t_linkedlist_node	*copy_linked_list(t_linkedlist_node *original);
TreeNode			*create_node(const char *value);
t_linkedlist_node	*create_node_l(char *data);
int					open_input_file(t_linkedlist_node *token_list);
int					open_output_file(t_linkedlist_node *token_list);
char				*get_fileout(t_linkedlist_node *token_list);
char				*get_filein(t_linkedlist_node *token_list);
void				redirect_file_descriptors(int input_fd, int output_fd);
void				execute_command(const char *command, int input_fd, int output_fd, char **envp);
void				child_process(TreeNode *tree, int input_fd, int output_fd, char **envp);
void				search_tokens(t_linkedlist_node *token_list, char **env);
TreeNode			*create_binary_tree(t_linkedlist_node *current);
void				free_tree(TreeNode *node);
char*				replace_env_double_single(const char * str);
bool				is_double_then_single(const char *str);
char				*replace_env_vars(const char *str);
void remove_lt_and_next(t_linkedlist_node **token_list);
void print_tree_reverse_in_order(TreeNode *root, int level);

#endif