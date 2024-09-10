/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:13:17 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/10 11:21:27 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_cd(char *path)
{
    char cwd[1024]; // Buffer to store the current working directory
    if (path == NULL)
    {
        fprintf(stderr, "cd: missing argument\n");
        return 1;
    }
    if (strcmp(path, "-") == 0)
    {
        fprintf(stderr, "cd: '-' option not supported\n");
        return 1;
    }
    if (chdir(path) != 0)
    {
        perror("cd");
        return 1;
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("cd");

    return 0;
}

int ft_export(char *var)
{
    if (var == NULL)
    {
        // List all environment variables in the format used by bash
        extern char **environ;
        char **env = environ;
        while (*env)
        {
            printf("declare -x %s\n", *env);
            env++;
        }
        return 0;
    }
    else if (strchr(var, '=') == NULL)
    {
        fprintf(stderr, "export: invalid format, use VAR=value\n");
        return 1;
    }
    if (putenv(var) != 0)
    {
        perror("export");
        return 1;
    }
    return 0;
}

int ft_unset(char *var)
{
    if (var == NULL)
    {
        fprintf(stderr, "unset: missing argument\n");
        return 1;
    }
    if (unsetenv(var) != 0)
    {
        perror("unset");
        return 1;
    }
    return 0;
}

void ft_exit(void)
{
    exit(0); 
}

int handle_builtins(t_linkedlist_node *tokens)
{
    if (tokens == NULL || tokens->data == NULL) {
        return 0; // No built-in command to handle
    }

    if (strcmp(tokens->data, "cd") == 0) {
        if (tokens->next && tokens->next->data) {
            if (ft_cd(tokens->next->data) != 0 && !tokens->next->data) {
                fprintf(stderr, "cd: %s: No such file or directory\n", tokens->next->data);
            }
        }
        return 1; 
    }
    else if (strcmp(tokens->data, "export") == 0) {
        if (tokens->next && tokens->next->data) {
            if (ft_export(tokens->next->data) != 0) {
                fprintf(stderr, "export: Invalid argument\n");
            }
        } else {
            if (ft_export(NULL) != 0) {
                fprintf(stderr, "export: Failed to list environment variables\n");
            }
        }
        return 1; 
    }
    else if (strcmp(tokens->data, "unset") == 0) {
        if (tokens->next && tokens->next->data) {
            printf("Unsetting variable: %s\n", tokens->next->data);
            if (ft_unset(tokens->next->data) != 0) {
                fprintf(stderr, "unset: Invalid argument\n");
            }
        } else {
            if (ft_unset(NULL) != 0) {
                fprintf(stderr, "unset: Failed to unset environment variable\n");
            }
        }
        return 1; 
    }
    else if (strcmp(tokens->data, "exit") == 0) {
        printf("Exiting shell\n");
        ft_exit(); 
        return 1; 
    }

    return 0; 
}
