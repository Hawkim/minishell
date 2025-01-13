/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabanna <jabanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:41:31 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/13 17:08:25 by jabanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// everthing related to signal

//  Handler for the SIGQUIT signal.
void	interrupt_handler(int signal)
{
	(void)signal;
	free_shell();
	exit(130);
}

//  Handler for the SIGINT signal
// exit 131 State not recoverable

void	quit_handler(int signal)
{
	(void)signal;
	free_shell();
	exit(131);
}

//print a new line when the user presses Ctrl+C
void	main_loop_handler(int signal)
{
	(void)signal;
	if (signal == SIGINT)
	{
		g_minishell.exit_code = 130;
	}
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// change input signal to avoid signals to respond with parent shell
void	change_signals(void)
{
	signal(SIGINT, main_loop_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_handler(int signal)
{
	(void)signal;
	printf("\n");
	free_shell();
	exit(130);
}
