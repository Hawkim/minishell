/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:05:20 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 13:31:51 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//wait for the child processes to finish
// WIFEXITED : returns true if the child terminated normally
// WEXITSTATUS : returns the exit status of the child

void	wait_pid(int pid[MAX_PID], int id)
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
		g_minishell.exit_code = WEXITSTATUS(wstatus);
}

void	check_pid(t_command **cmd, pid_t pid[MAX_PID], int id)
{
	if (pid[id] == -1)
	{
		free_shell();
		exit(11);
	}
	if (pid[id] == 0)
		exe_child(*cmd);
}
