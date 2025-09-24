/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:15:41 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 17:59:07 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_getcwd_error(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("chdir: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	free(cwd);
	return (0);
}

int	count_arguments(t_token *token)
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
	return (mdr_args);
}

char	*get_target_directory(t_token *token, t_mini *mini, int mdr_args)
{
	char	*target;

	if (mdr_args == 1)
	{
		target = get_value(mini->env, "HOME");
		if (!target)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else
	{
		if (token->next->str[0] == '-' && token->next->str[1])
			return (NULL);
		target = token->next->str;
	}
	return (target);
}

int	update_pwd_variables(char *target, t_mini *mini)
{
	char	*oldpwd;
	char	*logical_path;
	char	*newpwd;

	oldpwd = get_value(mini->env, "PWD");
	if (oldpwd)
		update_or_add_var(mini, "OLDPWD", oldpwd);
	logical_path = build_logical_path(target, mini);
	newpwd = remove_trailing_slash(logical_path);
	free(logical_path);
	update_or_add_var(mini, "PWD", newpwd);
	free(newpwd);
	return (0);
}
