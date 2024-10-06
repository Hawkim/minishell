/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:58:53 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/27 17:11:22 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	args_error(void)
{
	print_error("exit: ", NULL, "too many arguments.");
	g_minishell.exit_code = 1;
	return (0);
}

int	exit_num_error(char **exec)
{
	print_error("exit: ", exec[1], ": numeric argument required.");
	exit(2);
	return (1);
}

// exits the current shell
// exit sucess -> 0
// exit failure -> non 0
// check if numeric -> check if args valid -> exit
// if not -> print error msg , exit with status 1
int	ft_exit(char **exec)
{
	int	result;

	result = 0;
	if (exec[1] && exec[2])
	{
		if (!ft_long(exec[1]))
			exit_num_error(exec);
		args_error();
		return (1);
	}
	else if (exec[1] && ft_long(exec[1]))
		result = ft_atol(exec[1]);
	else if (exec[1] && !ft_long(exec[1]))
		exit_num_error(exec);
	g_minishell.exit_code = result;
	printf("exit\n");
	free_minishell();
	exit(g_minishell.exit_code);
	return (0);
}
