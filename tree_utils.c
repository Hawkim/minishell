#include "minishell.h"


TreeNode	*create_node(const char *value /*token->data*/)
{
	TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
	if (new_node == NULL)
	{
		perror("Failed to allocate memory for TreeNode");
		exit(EXIT_FAILURE);
	}
	new_node->value = strdup(value);
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

// void	search_in_tokens(t_linkedlist_node *token_list)
// {
// 	t_linkedlist_node	*current;
// 	char				*left_child_val;
// 	TreeNode			*root;

// 	current = token_list;
// 	while (current != NULL && strcmp(current->data, "|") != 0)
// 	{
// 		current = current->next;
// 	}
// 	if (strcmp(current->data, "|") == 0)
// 		root = create_node(current->data);
// 	root->left = create_lchild(root, current);
// }

TreeNode *create_tree_from_tokens(t_linkedlist_node *token_list) {
    if (token_list == NULL) return NULL;

    TreeNode *root = NULL;
    TreeNode *current_node = NULL;
    t_linkedlist_node *current_token = token_list;
    t_linkedlist_node *pipe_start = NULL;
    
    // Process tokens to create tree nodes
    while (current_token != NULL) {
        char *token = (char *)current_token->data;
        if (strcmp(token, "|") == 0) {
            // Create the root node when first pipe is encountered
            if (root == NULL) {
                root = create_node(token);
                current_node = root;
                pipe_start = current_token->next;
            } else {
                // Create a new right child node for the existing node
                TreeNode *new_node = create_node(token);
                current_node->right = new_node;
                new_node->parent = current_node;
                current_node = new_node;
                pipe_start = current_token->next;
            }
        } else {
            // Create a left child node for the current node
            if (pipe_start != NULL && current_node != NULL) {
                current_node->left = create_node(token);
                current_node->left->parent = current_node;
                current_node = current_node->left;
            } else if (root == NULL) {
                // Handle case where root node has not been created
                root = create_node(token);
                current_node = root;
            } else {
                // Add tokens before the first pipe to the left child of the root
                if (current_node != NULL && current_node->left == NULL) {
                    current_node->left = create_node(token);
                    current_node->left->parent = current_node;
                }
            }
        }
        current_token = current_token->next;
    }
    
    // Final adjustment of the tree structure
    if (pipe_start != NULL && current_node != NULL) {
        current_node->right = create_node("final_node");
    }

    return root;
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// // Create a new node with a specific value
	char input[] = "a | b";
	t_linkedlist_node *tokens = ftlexer(input, envp);
	// TreeNode *node = create_node(tokens->data);
	
	// // Print the value of the created node
	// printf("Node value: %s\n", node->value);

	// // Free the allocated memory
	// free(node->value);
	// free(node);
    // Create a root node
    // TreeNode *root = create_node("root_command");
    // printf("Root node value: %s\n", root->value);

	TreeNode *tree = create_tree_from_tokens(tokens);
    // Create a left child for the root node
    // TreeNode *left_child = create_lchild(root, "left_child_command");
	// TreeNode *right_child = create_rchild(root, "RR");
    // if (left_child != NULL)
    // {
    //     printf("Left child node value: %s\n", left_child->value);
    //     printf("Left child parent value: %s\n", left_child->parent->value);
	// 	printf("right child node value: %s\n", right_child->value);
    //     printf("right child parent value: %s\n", right_child->parent->value);
    // }
	printf("root = %s\n", tree->value);
	printf("left child = %s\n", tree->left->value);
	printf("right child = %s\n", tree->right->value);
    // Clean up allocated memory
    free_tree(tree);

    return 0;
}
