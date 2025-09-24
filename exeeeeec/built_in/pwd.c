/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:24:15 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/20 21:24:15 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_token *tokens)
{
	char	*cwd;
	t_token	*next;

	next = tokens->next;
	if (next && next->str[0] == '-' && next->str[1])
	{
		next->str[2] = 0;
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd(next->str, 2);
		ft_putstr_fd(": invalid option\npwd: usage: pwd [-LP]\n", 2);
		return (2);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
