/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:58:53 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 13:31:51 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	args_error(void)
{
	print_error("exit: ", NULL, "too many arguments.");
	g_minishell.exit_code = 1;
	return (0);
}

int	exit_num_error(char **exe)
{
	print_error("exit: ", exe[1], ": numeric argument required.");
	exit(2);
	return (1);
}

// exits the current shell
// exit sucess -> 0
// exit failure -> non 0
// check if numeric -> check if args valid -> exit
// if not -> print error msg , exit with status 1
int	ft_exit(char **exe)
{
	int	result;

	result = 0;
	if (exe[1] && exe[2])
	{
		if (!ft_long(exe[1]))
			exit_num_error(exe);
		args_error();
		return (1);
	}
	else if (exe[1] && ft_long(exe[1]))
		result = ft_atol(exe[1]);
	else if (exe[1] && !ft_long(exe[1]))
		exit_num_error(exe);
	g_minishell.exit_code = result;
	printf("exit\n");
	free_shell();
	exit(g_minishell.exit_code);
	return (0);
}
