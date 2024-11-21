/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:10:44 by nal-haki          #+#    #+#             */
/*   Updated: 2024/11/21 14:03:36 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_minishell	g_minishell;

void	read_a_line(void)
{
	g_minishell.parser = init_parser();
	g_minishell.parser->input = readline("minishell > ");
	if (if_eof(g_minishell.parser->input))
	{
		printf("exit\n");
		free_shell();
		exit(0);
	}
	add_history(g_minishell.parser->input);
}

// open terminal
// opens a command prompt to the user in an infinite loop
// change the response to received signals
// clear the struct and ready for next input
// open a prompt and wait for the input
// send to parsing & exeute

void	shell_loop(void)
{
	while (1)
	{
		change_signals();
		free_parser();
		free_command();
		read_a_line();
		if (!start_tokenization())
			continue ;
		start_exeution();
	}
}

// first initialize the global structure with the envp 
// parameter's list (converted into a hashtable)
// point all structures to NULL

static int	init_error(int flag)
{
	if (flag == 12)
		ft_putstr_fd("Error! No environment variables detected.", 2);
	else if (flag == 1)
		ft_putstr_fd("Invalid STDIN.", 2);
	else if (flag == 2)
	{
		ft_putstr_fd("Invalid arguments bro.", 2);
		flag--;
	}
	return (flag);
}

int	main(int argc, char **argv, char **envp)
{
	if (!envp[0])
		exit(init_error(12));
	if (!isatty(0))
		exit(init_error(1));
	if (argc > 1 && argv)
	{
		free_shell();
		exit(init_error(2));
	}
	init_shell(envp);
	shell_loop();
	return (0);
}
