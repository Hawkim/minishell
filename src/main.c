/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:10:44 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 13:22:19 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_minishell  *g_minishell;
t_minishell1	g_minishell1;

void	read_a_line(t_minishell *g_minishell)
{
	g_minishell->parser = init_parser(g_minishell);
	g_minishell->parser->input = readline("minishell > ");
	if (if_eof(g_minishell->parser->input))
	{
		printf("exit\n");
		free_shell(g_minishell);
		exit(0);
	}
	add_history(g_minishell->parser->input);
}

// open terminal
// opens a command prompt to the user in an infinite loop
// change the response to received signals
// clear the struct and ready for next input
// open a prompt and wait for the input
// send to parsing & exeute

void	shell_loop(t_minishell *g_minishell)
{
	while (1)
	{
		change_signals();
		free_parser(g_minishell);
		free_command(g_minishell);
		read_a_line(g_minishell);
		if (!start_tokenization(g_minishell))
			continue ;
		start_exeution(g_minishell);
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

// int	main(int argc, char **argv, char **envp)
// {
// 	t_minishell	*g_minishell;

// 	if (!envp[0])
// 		exit(init_error(12));
// 	if (!isatty(0))
// 		exit(init_error(1));
// 	if (argc > 1 && argv)
// 	{
// 		free_shell(g_minishell);
// 		exit(init_error(2));
// 	}
// 	init_shell(envp, g_minishell);
// 	shell_loop(g_minishell);
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*g_minishell;

	if (!envp[0])
		exit(init_error(12));
	if (!isatty(0))
		exit(init_error(1));
	if (argc > 1 && argv)
		exit(init_error(2));
	g_minishell = malloc(sizeof(t_minishell));
	if (!g_minishell)
		exit(init_error(3));
	init_shell(envp, g_minishell);
	shell_loop(g_minishell);
	printf("%d\n", g_minishell1.signal_code);
	free_shell(g_minishell);
	return (0);
}
