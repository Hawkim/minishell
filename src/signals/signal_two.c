/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:41:31 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 13:31:51 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// everthing related to signal
void	get_heredoc_child_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_handler);
}

void	get_heredoc_parent_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	parent_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_minishell.exit_code = 131;
	}
	if (signal == SIGINT)
	{
		printf("\n");
		g_minishell.exit_code = 130;
	}
}

// changes the default responses of the signals by parent shell
// avoid the signals respond to the childshell
void	exe_commands_parent_signals(void)
{
	signal(SIGQUIT, parent_handler);
	signal(SIGINT, parent_handler);
}

// changes the default signals received by specific shortcuts
// to avoid that these signals will respond to the parent shell,
// instead of the current.
void	exe_commands_child_signals(void)
{
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, quit_handler);
}
