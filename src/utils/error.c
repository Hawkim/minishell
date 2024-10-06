/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:05:47 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/07 00:53:24 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// everthing related to error
// If pid is negative, error while executing the command
// If fd is negative,  error while opening the file

int	heredoc_error(int *fd)
{
	if (fd)
		close(fd[0]);
	else
	{
		free_minishell();
		exit(-54);
	}
	return (-3);
}

void	print_error(char *src, char *elem, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(src, 2);
	if (elem)
	{
		ft_putstr_fd(BLACK, 2);
		ft_putstr_fd(elem, 2);
		ft_putstr_fd(BLACK, 2);
	}
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
}

// ouput to STDERR 
void	cmd_error(t_command *cmd, int nb)
{
	if (nb == 1)
	{
		g_minishell.exit_code = 127;
		print_error("cmd: ", cmd->exec[0], ": no such file in directory");
	}
	else
	{
		if (!ft_strncmp(cmd->exec[0], ":\0", 2)
			|| !ft_strncmp(cmd->exec[0], "!\0", 2)
			|| !ft_strncmp(cmd->exec[0], "#\0", 2))
			return ;
		else
		{
			g_minishell.exit_code = 127;
			print_error("cmd: `", cmd->exec[0], "\': command not found.");
		}
	}
}

// print the error message corresponding to the errno value
// 13	/* Permission denied */
// 2	/* No such file or directory */
void	return_error(char *filename, int error_number)
{
	if (error_number == EACCES)
	{
		g_minishell.exit_code = 126;
		print_error(NULL, filename, ": Is a directory.");
	}
	else if (error_number == ENOENT)
	{
		g_minishell.exit_code = 1;
		print_error(NULL, filename, ": no such file or directory.");
	}
	else
	{
		g_minishell.exit_code = 127;
		print_error(NULL, filename, ": command not found.");
	}
}
