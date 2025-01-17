/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:05:20 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 13:20:06 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//wait for the child processes to finish
// WIFEXITED : returns true if the child terminated normally
// WEXITSTATUS : returns the exit status of the child

void	wait_pid(int pid[MAX_PID], int id, t_minishell *g_minishell)
{
	int	max_id;
	int	wstatus;

	if (id == -1)
		return ;
	max_id = id;
	id = -1;
	wstatus = 0;
	while (++id <= max_id)
		waitpid (pid[id], &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_minishell->exit_code = WEXITSTATUS(wstatus);
}

void	check_pid(t_command **cmd, pid_t pid[MAX_PID], int id,
	t_minishell *g_minishell)
{
	if (pid[id] == -1)
	{
		free_shell(g_minishell);
		exit(11);
	}
	if (pid[id] == 0)
		exe_child(*cmd, g_minishell);
}
