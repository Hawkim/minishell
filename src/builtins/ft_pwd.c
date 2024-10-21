/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:51:37 by nal-haki          #+#    #+#             */
/*   Updated: 2024/10/21 14:10:29 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_tok_invalid(char *tok)
{
	if (tok[0] == '-')
		return (1);
	return (0);
}

int	ft_pwd(char **exe)
{
	char	*pwd;

	if (exe[1] && if_tok_invalid(exe[1]))
	{
		print_error("pwd:`", exe[1], "\': invalid option.");
		return (2);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		free(pwd);
		pwd = keyy_search("PWD");
		printf("%s\n", pwd);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	return (0);
}
