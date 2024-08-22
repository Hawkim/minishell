/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:39:40 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/22 13:07:11 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#define MAX_ENV_VAR_LENGTH 256  // Define a threshold for ignoring large env vars

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <ctype.h>
# include <stdbool.h>

# define INITIAL "INITIAL"
# define IN_QUOTE "IN_QUOTE"
# define IN_SQUOTE "IN_SQUOTE"

typedef struct ll_node
{
    struct ll_node *next;
    char *data;
    char *state;
} t_linkedlist_node;

typedef struct TreeNode
{
    char *value; // Command or operator
    struct TreeNode *left; // Left child (for commands)
    struct TreeNode *right; // Right child (for pipes)
    struct TreeNode *parent;
} TreeNode;

t_linkedlist_node *ftlexer(char *s); // Updated declaration to match definition

void	append(t_linkedlist_node **list, char *data);
void				append_large_env(t_linkedlist_node **head, const char *data);
void print_tokens(t_linkedlist_node *list);
t_linkedlist_node* replace_large_env_vars(t_linkedlist_node *tokens);

char *replace_env_vars(const char *str);
char *replace_env_double_single(const char *str);
bool check_quotes(const char *str);

#endif // MINISHELL_H
// minishell.h
