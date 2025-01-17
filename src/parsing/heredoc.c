/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:14:21 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 11:51:22 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// heredoc: redirect the output of a command to a file
//  prompted for input
// then the input is written to the file when the command is exeuted
// keep prompting the user until it finds the delimiter 
// if EOF is found -> error
// fd is invaid -> error

// WEXITSTATUS : returns the exit status of the child
// WIFEXITED : returns true if the child terminated normally
int	heredoc(char *name, t_minishell *g_minishell)
{
	int	pid;
	int	fd[2];
	int	wstatus;

	if (pipe(fd) == -1)
		return (heredoc_error(NULL, g_minishell));
	pid = fork();
	if (pid == -1)
		return (heredoc_error(NULL, g_minishell));
	if (!pid)
	{
		close(fd[0]);
		write_to_pipe(ft_strdup(name), &fd[1]);
	}
	get_heredoc_parent_signal();
	close(fd[1]);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
		return (heredoc_error(fd, g_minishell));
	return (fd[0]);
}
