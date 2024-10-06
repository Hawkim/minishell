/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:19:19 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/26 22:39:17 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_builtin(t_command *cmd)
{
	if (!ft_strncmp(cmd->exec[0], "cd\0", 3))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "echo\0", 5))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "export\0", 7))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "env\0", 4))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "exit\0", 5))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "pwd\0", 4))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "unset\0", 6))
		return (1);
	return (0);
}
