/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:25:55 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 17:16:55 by ilsadi           ###   ########.fr       */
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
		ft_putstr_fd(": invalid option\ncd: usage: "
			"cd [-L|[-P [-e]] [-@]] [dir]\n", 2);
		return (2);
	}
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(token->next->str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

int	cd(t_token *token, t_mini *mini)
{
	int		mdr_args;
	char	*target;

	handle_getcwd_error();
	mdr_args = count_arguments(token);
	if (mdr_args > 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	target = get_target_directory(token, mini, mdr_args);
	if (!target)
	{
		if (mdr_args == 1)
			return (1);
		return (cd_error(token));
	}
	if (chdir(target) != 0)
		return (cd_error(token));
	return (update_pwd_variables(target, mini));
}
