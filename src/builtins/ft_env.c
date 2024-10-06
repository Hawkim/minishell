/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:15:28 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/27 17:10:53 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Prints the env complete list of environment variables
int	ft_env(t_command *cmd)
{
	char	**exec;
	int		result;
	size_t	i;

	exec = cmd->exec;
	result = 127;
	if (!key_search("PATH"))
		print_error("env: ", exec[0], ": no such file or directory.");
	else if (!exec[1] || !*exec[1])
	{
		i = -1;
		while (cmd->envp[++i])
			printf("%s\n", cmd->envp[i]);
		result = 0;
	}
	return (result);
}
