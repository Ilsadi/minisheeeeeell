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
		ft_putstr_fd(": invalid option\ncd: usage:"
			"cd [-L|[-P [-e]] [-@]] [dir]\n", 2);
		return (2);
	}
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(token->next->str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

static char	*concat_paths(const char *base, const char *sub)
{
	char	*joined;
	size_t	len;
	char	*tmp;

	len = strlen(base);
	if (len > 0 && base[len - 1] == '/')
		joined = ft_strjoin(base, sub);
	else
	{
		tmp = ft_strjoin(base, "/");
		joined = ft_strjoin(tmp, sub);
		free(tmp);
	}
	return (joined);
}

char	*remove_trailing_slash(const char *path)
{
	size_t	len;
	char	*trimmed;

	len = strlen(path);
	if (len > 1 && path[len - 1] == '/')
	{
		trimmed = strdup(path);
		trimmed[len - 1] = '\0';
		return (trimmed);
	}
	return (strdup(path));
}

static int	handle_getcwd_error(void)
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

static int	count_arguments(t_token *token)
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

static char	*get_target_directory(t_token *token, t_mini *mini, int mdr_args)
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

static char	*build_logical_path(char *target, t_mini *mini)
{
	char	*pwd_current;
	char	*logical_path;

	if (target[0] == '/')
		logical_path = strdup(target);
	else
	{
		pwd_current = get_value(mini->env, "PWD");
		if (!pwd_current)
			pwd_current = "";
		logical_path = concat_paths(pwd_current, target);
	}
	return (logical_path);
}

static int	update_pwd_variables(char *target, t_mini *mini)
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
