// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   tree.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/14 09:28:57 by jabanna           #+#    #+#             */
// /*   Updated: 2024/08/14 09:47:55 by jabanna          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// // typedef struct TreeNode
// // {
// // 	char			*value; // Command or operator
// // 	struct TreeNode	*left; // Left child (for commands)
// // 	struct TreeNode	*right; // Right child (for pipes)
// // } TreeNode;

// typedef struct param{
// 	char				*s;
// 	int					*i;
// 	char				**current_token;
// 	t_linkedlist_node	**token_list;
// 	char				**state;
// }	t_ProcessParams;

// static void	reset_current_token(char **current_token)
// {
// 	free(*current_token);
// 	*current_token = malloc(1024);
// 	if (!*current_token)
// 	{
// 		perror("malloc failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	(*current_token)[0] = '\0';
// }

// static void	append_token_if_not_empty(char **current_token,
// 					t_linkedlist_node **token_list)
// {
// 	if (strlen(*current_token) > 0)
// 	{
// 		append(token_list, *current_token);
// 		reset_current_token(current_token);
// 	}
// }

// static void	handle_space(char **current_token, t_linkedlist_node **token_list)
// {
// 	append_token_if_not_empty(current_token, token_list);
// }

// static void	handle_operator(char **current_token,
// 					t_linkedlist_node **token_list, char op)
// {
// 	char	operator[2];

// 	append_token_if_not_empty(current_token, token_list);
// 	operator[0] = op;
// 	operator[1] = '\0';
// 	append(token_list, operator);
// }

// static void	process_character(t_ProcessParams *params)
// {
// 	if (params->s[*params->i] == ' ')
// 		handle_space(params->current_token, params->token_list);
// 	else if (params->s[*params->i] == '\"')
// 		*params->state = IN_QUOTE;
// 	else if (params->s[*params->i] == '\'')
// 		*params->state = IN_SQUOTE;
// 	else if (strchr("|><&", params->s[*params->i]))
// 		handle_operator(params->current_token,
// 			params->token_list, params->s[*params->i]);
// 	else
// 		strncat(*params->current_token, &params->s[*params->i], 1);
// }

// static void	process_state(t_ProcessParams *params)
// {
// 	if (strcmp(*params->state, INITIAL) == 0)
// 		process_character(params);
// 	else if (strcmp(*params->state, IN_QUOTE) == 0)
// 	{
// 		if (params->s[*params->i] == '\"')
// 			*params->state = INITIAL;
// 		else
// 			strncat(*params->current_token, &params->s[*params->i], 1);
// 	}
// 	else if (strcmp(*params->state, IN_SQUOTE) == 0)
// 	{
// 		if (params->s[*params->i] == '\'')
// 			*params->state = INITIAL;
// 		else
// 			strncat(*params->current_token, &params->s[*params->i], 1);
// 	}
// }
// // Function to create a new tree node
// TreeNode* create_node(char *value)
// {
// 	TreeNode *new_node = malloc(sizeof(TreeNode));
// 	if (!new_node) {
// 		perror("malloc failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	new_node->value = strdup(value);
// 	new_node->left = NULL;
// 	new_node->right = NULL;
// 	return (new_node);
// }

// void free_tree(TreeNode *node) {
//     if (node) {
//         free_tree(node->left);
//         free_tree(node->right);
//         free(node->value);
//         free(node);
//     }
// }

// TreeNode* build_parse_tree(t_linkedlist_node *token_list) {
//     TreeNode *root = NULL;
//     TreeNode *current = NULL;

//     while (token_list) {
//         char *token = token_list->data; // Assuming token_list has a data field
//         if (strcmp(token, "|") == 0) {
//             // Create a new node for the command before the pipe
//             if (current) {
//                 // If there's already a current command, link it
//                 current->right = create_node(token_list->next->data); // Next token after pipe
//                 current = current->right; // Move current to the right child
//             }
//         } else {
//             // Create a new node for the command
//             TreeNode *new_node = create_node(token);
//             if (!root) {
//                 root = new_node; // Set root if it's the first command
//                 current = root; // Set current to root
//             } else {
//                 current->right = new_node; // Link to the right
//                 current = new_node; // Move current to the new node
//             }
//         }
//         token_list = token_list->next; // Move to the next token
//     }
//     return root;
// }

// TreeNode* ftlexer(char *s, char **envp) {
//     t_linkedlist_node *token_list = NULL;
//     char *state = INITIAL;
//     char *current_token = malloc(1024);
//     int i = 0;

//     if (!current_token) exit(EXIT_FAILURE);
//     current_token[0] = '\0';

//     t_ProcessParams params = {s, &i, &current_token, &token_list, &state};
//     while (s[i] != '\0') {
//         process_state(&params);
//         i++;
//     }
//     append_token_if_not_empty(&current_token, &token_list);
    
//     // Build the parse tree from the token list
//     TreeNode *parse_tree = build_parse_tree(token_list);
    
//     // Free the token list and current token memory
//     free(current_token);
//     // free_linkedlist(token_list); // Assuming you have a function to free the linked list
//     return parse_tree;
// }

// #include <stdio.h>

// void print_tree(TreeNode *node, int level) {
//     if (node == NULL) {
//         return;
//     }

//     // Print the right child first (to display it on the right side)
//     print_tree(node->right, level + 1);

//     // Print the current node value with indentation
//     for (int i = 0; i < level; i++) {
//         printf("   "); // Indentation for each level
//     }
//     printf("%s\n", node->value);

//     // Print the left child
//     print_tree(node->left, level + 1);
// }


// int main(int argc, char **argv) {
//     char *command_line = "ls -l | grep .c | sort";
//     TreeNode *parse_tree = ftlexer(command_line, NULL);

//     // You can now traverse the parse tree or print it
//     // For example, a simple traversal function could be implemented here

// 	printf("Parse Tree:\n");
//     print_tree(parse_tree, 0);
	
//     free_tree(parse_tree); // Don't forget to free the tree after use
//     return 0;
// }
