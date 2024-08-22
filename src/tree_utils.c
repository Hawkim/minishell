/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:38:47 by jabanna           #+#    #+#             */
/*   Updated: 2024/08/22 10:09:19 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


TreeNode	*create_node(const char *value /*token->data*/)
{
	TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
	if (new_node == NULL)
	{
		perror("Failed to allocate memory for TreeNode");
		exit(EXIT_FAILURE);
	}
	new_node->value = ft_strdup(value);
	if (new_node->value == NULL)
	{
		perror("Failed to allocate memory for node value");
		free(new_node);
		exit(EXIT_FAILURE);
	}
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	return new_node;
}

TreeNode	*create_lchild(TreeNode *root, const char *value)
{
	TreeNode	*left_child;

	left_child = create_node(value);
	if (!root)
		return (NULL);
	root->left = left_child;
	left_child->parent = root;
	// left_child->left = NULL;
	// left_child->right = NULL;
	return (left_child);
}

TreeNode	*create_rchild(TreeNode *root, const char *value)
{
	TreeNode	*right_child;

	right_child = create_node(value);
	if (!root)
		return (NULL);
	root->right = right_child;
	right_child->parent = root;
	// right_child->right = NULL;
	// right_child->right = NULL;
	return (right_child);
}

void free_tree(TreeNode *node)
{
	if (node != NULL)
	{
		free_tree(node->left);
		free_tree(node->right);
		free(node->value);
		free(node);
	}
}



// TreeNode	*search_in_tokens(t_linkedlist_node *current)
// {
// 	// t_linkedlist_node	*current;
// 	char				*left_child_val;
// 	TreeNode			*root;
// 	char				*command;
// 	TreeNode			*firstnode;
// 	TreeNode			*secondnode;

// 	// current = token_list;
// 	root = NULL;
// 	command = strdup(" ");
// 	while (current != NULL && strcmp(current->data, "|") != 0)
// 	{
// 		command = ft_strjoin(command, current->data);
// 		if (strcmp(current->next->data, "|" ) != 0 && current->next != NULL)
// 			command = ft_strjoin(command, " ");
// 		current = current->next;
// 	}
// 	if (command != NULL)
// 		firstnode = create_node(command);
// 	command = NULL;
// 	// if (strcmp(current->data, "|") == 0)
// 	if (current != NULL && current->data != NULL)
// 	{
// 		root = create_node(current->data);
// 		firstnode->parent = root;
// 		root->left = firstnode;
// 		root->right = search_in_tokens(current->next);
// 		// return (search_in_tokens(current));
// 	}
	
// 	// root->left = create_lchild(root, command);
// 	// root->right = create_rchild(root, "RIGHTT");
// 	// root->right = search_in_tokens(token_list);
// 	return (root);
// }

TreeNode	*create_binary_tree(t_linkedlist_node *current)
{
	TreeNode *root ;
	TreeNode *firstnode ;
	char *command ;
	char *temp ;

	root= NULL;
	firstnode = NULL;
	command = ft_strdup("");
	temp = NULL;
	// Concatenate tokens before the first '|'
	while (current != NULL && ft_strncmp(current->data, "|", 1) != 0)
	{
		temp = ft_strjoin(command, current->data);
		// free(command);
		command = temp;
		if (current->next != NULL && ft_strncmp(current->next->data, "|", 1) != 0)
		{
			temp = ft_strjoin(command, " ");
			// free(command);
			command = temp;
		}
		current = current->next;
	}
	if (command != NULL && ft_strlen(command) > 0)
	{
		firstnode = create_node(command);
		free(command);  // Free the command after creating the node
	}
	// If current is not NULL and points to a '|', create a root node
	if (current != NULL && current->data != NULL && ft_strncmp(current->data, "|", 1) == 0)
	{
		root = create_node(current->data);
		// Create the left child with tokens before the first '|'
		root->left = firstnode;
		if (firstnode != NULL)
			firstnode->parent = root;
		root->right = create_binary_tree(current->next);
	}
	else if (firstnode != NULL)
		root = firstnode;// If no more pipes, this is a leaf node
	return (root);
}

void redirect_file_descriptors(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO); // Redirect input
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO); // Redirect output
		close(output_fd);
	}
}

void execute_command(const char *command, int input_fd, int output_fd, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_split(command, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		fprintf(stderr, "Error: Command not found: %s\n", cmd[0]);
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
		exit(EXIT_FAILURE);
	}
	// if (input_fd != STDIN_FILENO)
	// {
	// 	dup2(input_fd, STDIN_FILENO); // Redirect input
	// 	close(input_fd);
	// }
	// if (output_fd != STDOUT_FILENO)
	// {
	// 	dup2(output_fd, STDOUT_FILENO); // Redirect output
	// 	close(output_fd);
	// }
	redirect_file_descriptors(input_fd, output_fd);
	if (execve(path, cmd, envp) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void child_process(TreeNode *tree, int input_fd, char **envp)
{
	int pipe_fd[2];

	if (tree == NULL)
		return;
	if (ft_strncmp(tree->value, "|", 1) == 0)
	{
		// Handle the pipe symbol by setting up a pipe and processing left and right children
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		// Process the left child
	 if (tree->left != NULL)
        {
            pid_t left_pid = fork();
            if (left_pid == 0)
            {
                // In the left child process
                close(pipe_fd[0]);
                if (input_file != NULL)
                {
                    int file_fd = open(input_file, O_RDONLY);
                    if (file_fd == -1)
                    {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                    dup2(file_fd, STDIN_FILENO);
                    close(file_fd);
                }
                else if (input_fd != STDIN_FILENO)
                {
                    dup2(input_fd, STDIN_FILENO);
                    close(input_fd);
                }
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
                child_process(tree->left, STDIN_FILENO, envp, NULL);
                exit(EXIT_SUCCESS);
            }
			else
			{
				// In the parent process
				close(pipe_fd[1]); // Close the write end of the pipe
				waitpid(left_pid, NULL, 0); // Wait for left child to finish
			}
		}
		// Process the right child
		if (tree->right != NULL)
		{
			pid_t right_pid = fork();
			if (right_pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (right_pid == 0)
			{
				// In the right child process
				close(pipe_fd[1]); // Close the write end of the pipe
				dup2(pipe_fd[0], STDIN_FILENO); // Redirect input from the pipe
				close(pipe_fd[0]); // Close the read end of the pipe
				child_process(tree->right, pipe_fd[0], envp, NULL);
				exit(EXIT_SUCCESS);
			}
			else
			{
				// In the parent process
				close(pipe_fd[0]); // Close the read end after use
				waitpid(right_pid, NULL, 0); // Wait for right child to finish
			}
		}
	}
	else
	{
		// If the node's value is not a pipe symbol, execute the command
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			// In the child process
			execute_command(tree->value, input_fd, STDOUT_FILENO, envp);
			exit(EXIT_SUCCESS);
		}
		else
		{
			// In the parent process
			waitpid(pid, NULL, 0); // Wait for the child process to finish
		}
	}
}

void	move_in_tree(TreeNode *tree, int i)
{
	if (tree == NULL)
		return ;
	if (tree->left != NULL)
		move_in_tree(tree->left, i);
	// exec();
	tree->value = ft_itoa(i);
	i++;
	if (tree->right != NULL)
		move_in_tree(tree->right, i);
}

void remove_lt_and_next(t_linkedlist_node **token_list)
{
	t_linkedlist_node *current = *token_list;
	t_linkedlist_node *prev = NULL;

	// Traverse the list
	while (current != NULL) {
		if (ft_strncmp(current->data, "<", 1) == 0 || ft_strncmp(current->data, ">", 1) == 0) {
			// Check if there's a next node
			if (current->next != NULL) {
				t_linkedlist_node *node_to_remove = current->next;

				// If `current` is the head of the list
				if (prev == NULL) {
					*token_list = node_to_remove->next;
				} else {
					prev->next = node_to_remove->next;
				}

				// Free the memory for the removed nodes
				free(current->data); // Free the data for the `<` node
				free(current->state); // Free the state for the `<` node
				free(current); // Free the `<` node itself

				free(node_to_remove->data); // Free the data for the following node
				free(node_to_remove->state); // Free the state for the following node
				free(node_to_remove); // Free the following node itself
				
				return; // Exit after removing the nodes
			} else {
				// No node to remove after `<`
				// Free the `<` node only
				if (prev == NULL) {
					*token_list = current->next;
				} else {
					prev->next = current->next;
				}

				free(current->data);
				free(current->state);
				free(current);

				return; // Exit after removing the `<` node
			}
		}

		// Move to the next node
		prev = current;
		current = current->next;
	}
	
	// If no `<` token was found
	fprintf(stderr, "Token `<` not found in the list.\n");
}

char *get_filein(t_linkedlist_node *token_list)
{
    if (token_list == NULL)
        return (NULL);
    while (token_list != NULL)
    {
        if (ft_strncmp(token_list->data, "<", 1) == 0 && token_list->next != NULL)
            return (token_list->next->data);
        token_list = token_list->next;
    }
    return (NULL);
}

char	*get_fileout(t_linkedlist_node *token_list)
{
	char	*fileout;

	fileout = NULL;
	if (token_list == NULL)
		return (NULL);
	while (token_list != NULL)
	{
		if (ft_strncmp(token_list->data, ">", 1) == 0)
			fileout = token_list->next->data;
		token_list = token_list->next;
	}
	if (fileout)
		return (fileout);
	else
		return (NULL);
}

void print_tree_reverse_in_order(TreeNode *root, int level) {
	if (root == NULL) return;

	// Recursively print the right subtree
	print_tree_reverse_in_order(root->right, level + 1);

	// Print the current node with indentation
	for (int i = 0; i < level; i++) {
		printf("    ");  // Print spaces for indentation
	}
	printf("%s\n", root->value);

	// Recursively print the left subtree
	print_tree_reverse_in_order(root->left, level + 1);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// char input[] = "echo '\"'\"'\"Hello, | world!\"'\"'\"' > output.txt | grep \" \" PATH hello\"'\"a ";
	// char input[] = "ls -l | wc -w $HOMEsjjfrkf$HOME";
	// char input[] = "< b ls -l | ls -m | ls -S | wc -m > fileout";
	char input[] = "ls -l | ls -m | ls -S | wc -m | ls -l | wc -w";
	t_linkedlist_node *tokens = ftlexer(input, envp);
	printf("Input file = %s\n", get_filein(tokens));
	printf("Output file = %s\n", get_fileout(tokens));
	// remove_lt_and_next(&tokens);
	// remove_lt_and_next(&tokens);
	// TreeNode	*root;
	// TreeNode *tree = search_in_tokens(tokens, root);
	TreeNode *tree = create_binary_tree(tokens);
	child_process(tree, STDIN_FILENO, envp, input_file);
	// printf("root = %s\n", tree->value);
	// printf("left child = %s\n", tree->left->value);
	// printf("right child = %s\n", tree->right->value);
	// printf("left child of right child = %s\n", tree->right->left->value);
	// printf("right child of right child = %s\n", tree->right->right->value);
	// printf("parent = %s\n", tree->left->parent->value);
	print_tree_reverse_in_order(tree, 0);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	move_in_tree(tree, 0);
	print_tree_reverse_in_order(tree, 0);
	free_tree(tree);
	return 0;
}
