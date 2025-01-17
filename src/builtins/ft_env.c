/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:15:28 by nal-haki          #+#    #+#             */
/*   Updated: 2025/01/17 11:51:22 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Prints the env complete list of environment variables
int	ft_env(t_command *cmd, t_minishell *g_minishell)
{
	char	**exe;
	int		result;
	size_t	i;

	exe = cmd->exe;
	result = 127;
	if (!keyy_search("PATH", g_minishell))
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
