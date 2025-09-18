/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:25:55 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/22 23:25:55 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	cd_error(t_token *token)
{
	if (token->next->str[0] == '-' && token->next->str[1])
	{
		token->next->str[2] = 0;
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(token->next->str, 2);
		ft_putstr_fd(": invalid option\ncd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n", 2);
		return (2);
	}
	if (chdir(token->next->str))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(token->next->str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int	cd(t_token *token, t_var **var)
{
	t_token	*current;
	int		mdr_args;

	mdr_args = 1;
	current = token->next;
	while (current && current->type == ARG)
	{
		mdr_args++;
		current = current->next;
	}
	if (mdr_args == 1)
	{
		if (!get_value(var, "HOME"))
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
		chdir(get_value(var, "HOME"));
	}
	else if (mdr_args == 2)
		return (cd_error(token));
	else
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}
