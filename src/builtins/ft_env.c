/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:15:28 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 14:10:29 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Prints the env complete list of environment variables
int	ft_env(t_command *cmd)
{
	char	**exe;
	int		result;
	size_t	i;

	exe = cmd->exe;
	result = 127;
	if (!keyy_search("PATH"))
		print_error("env: ", exe[0], ": no such file or directory.");
	else if (!exe[1] || !*exe[1])
	{
		i = -1;
		while (cmd->envp[++i])
			printf("%s\n", cmd->envp[i]);
		result = 0;
	}
	return (result);
}
