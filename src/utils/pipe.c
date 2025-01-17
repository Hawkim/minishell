/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:18:48 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 11:51:22 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// opens all necessary pipes by the previously defined PIPE endpoints
//determines the correct fd for input and output 

void	open_pipes(t_minishell *g_minishell)
{
	t_command	*cmd;

	cmd = g_minishell->command;
	while (cmd)
	{
		if (cmd->endpoint == PIPE)
		{
			if (pipe(cmd->fd_pipe) == -1)
			{
				free_shell(g_minishell);
				exit(11);
			}
			cmd->fd_out = cmd->fd_pipe[1];
			cmd->is_piped = 1;
			cmd->next->fd_in = cmd->fd_pipe[0];
			cmd->next->is_piped = 1;
		}
		cmd = cmd->next;
	}
}

void	write_to_pipe(char *limiter, int *fd)
{
	char	*line;
	int		len;

	get_heredoc_child_signal();
	line = readline("> ");
	len = ft_strlen(limiter);
	while (1)
	{
		if (!line)
			printf("minishell: warning: here-doc delimited by %s\n", limiter);
		if (!line || (!ft_strncmp(limiter, line, len) && !line[len]))
			break ;
		write(*fd, line, ft_strlen(line));
		write(*fd, "\n", 1);
		free(line);
		line = readline ("> ");
	}
	free(line);
	close(*fd);
	free(limiter);
	exit(0);
}
