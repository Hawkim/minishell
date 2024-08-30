/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:42:23 by nal-haki          #+#    #+#             */
/*   Updated: 2024/08/30 16:50:35 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_sig g_sig;

void sig_int(int code)
{
    (void)code;
    if (g_sig.pid == 0)
    {
        // Display a new prompt on a new line
        ft_putstr_fd("\nminishell > ", STDERR_FILENO);
        g_sig.exit_status = 1;
    }
    else
    {
        // If a child process was running
        ft_putstr_fd("\n", STDERR_FILENO);
        g_sig.exit_status = 130; // Exit status for SIGINT
    }
    g_sig.sigint = 1;
}

void sig_quit(int code)
{
    (void)code;
    // Do nothing when SIGQUIT is received
}
void sig_init(void)
{
    g_sig.sigint = 0;
    g_sig.sigquit = 0;
    g_sig.pid = 0;
    g_sig.exit_status = 0;
}
