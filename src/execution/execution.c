/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:32:18 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:09 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Create a execution envp object by allocating memory
// fill it fill in a list of strings with the exported environment variables

void	create_exec_envp(t_command *cmd)
{
	t_hashtable	*table;
	t_hashpair	*list;
	char		**envp;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	table = g_minishell.envp;
	envp = malloc (sizeof(char *) * (table->count + 1));
	while (i < table->size)
	{
		list = table->list[i];
		while (list)
		{
			if (list->attribute == GLOBAL)
				envp[j++] = ft_strnjoin(3, list->hash_key, "=",
						list->hash_value);
			list = list->next;
		}
		i++;
	}
	envp[j] = NULL;
	cmd->envp = envp;
}

// check for open fd and close them
// fd_type : should be closed on the input or output or both

void	close_fd(t_command *cmd, int fd_type)
{
	if ((fd_type == IN || fd_type == BOTH) && cmd->fd_in > 2)
		close(cmd->fd_in);
	if ((fd_type == OUT || fd_type == BOTH) && cmd->fd_out > 2)
		close(cmd->fd_out);
}

// executes the t_cmd list of commands
// first searched for in the "PATH" -> 
// check if the executable exists in each directory
// fork and execute the command 
// and then wait for the child to finish -> display prompt
// the fork is needed so the minishell itself wont be interruppted
// if pid = -1 -> error & exit
// if pid = 0 -> child processexecute the cmd
// parent process should wait for the child to finish 
// all the file descriptors should be closed
static void	empty_cmd(char	*error)
{
	if (!ft_strncmp(error, "\0", 1))
	{
		print_error("cmd: `", error, "\': Command not found.");
		g_minishell.exit_code = 127;
	}
	if (!ft_strncmp(error, ".\0", 2))
	{
		print_error("cmd: `", error, "\': Filename argument required.");
		g_minishell.exit_code = 2;
	}
}

void	exec_commands(t_command **cmd)
{
	pid_t		pid[MAX_PID];
	int			id;

	id = -1;
	while (*cmd)
	{
		exec_commands_parent_signals();
		(*cmd)->exec_path = get_cmd_path(*cmd);
		create_exec_envp(*cmd);
		if (!ft_strncmp((*cmd)->exec[0], "\0", 1)
			|| !ft_strncmp((*cmd)->exec[0], ".\0", 2))
			empty_cmd((*cmd)->exec[0]);
		else if ((*cmd)->fd_in == -1 || (*cmd)-> fd_out == -1)
			return_error((*cmd)->error_file, (*cmd)->error_number);
		else if ((*cmd)->exec_path && if_fork_needed (*cmd))
		{
			pid[++id] = fork();
			check_pid(cmd, pid, id);
		}
		close_fd(*cmd, BOTH);
		*cmd = (*cmd)->next;
	}
	wait_pid (pid, id);
}

// excute all the commands from the prompt line
// open all the pipes
// read and apply redir and heredoc
// execute the cmds

void	start_execution(void)
{
	t_command	*cmd;

	cmd = g_minishell.command;
	open_pipes();
	if (!define_redir())
		return ;
	while (cmd)
	{
		exec_commands(&cmd);
		if (cmd)
			cmd = cmd->next;
	}
}
