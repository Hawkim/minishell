/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:39:40 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/15 15:48:55 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

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

t_linkedlist_node	*ftlexer(char *s, char **envp);
// TreeNode* ftlexer(char *s, char **envp);
void				append(t_linkedlist_node **token_list, char *s);
void				print_tokens(t_linkedlist_node *list);
void				search_tokens(t_linkedlist_node *token_list, char **env);
char				*search_env(char *var, char **env);
char				*search_string(char *s, char **env);

t_linkedlist_node *ftlexer(char *s, char **envp);
void print_tokens(t_linkedlist_node *tokens);


#endif