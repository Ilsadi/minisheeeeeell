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
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(token->next->str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

static char	*concat_paths(const char *base, const char *sub)
{
	char	*joined;
	size_t	len = strlen(base);

	if (len > 0 && base[len - 1] == '/')
		joined = ft_strjoin(base, sub);
	else
	{
		char *tmp = ft_strjoin(base, "/");
		joined = ft_strjoin(tmp, sub);
		free(tmp);
	}
	return (joined);
}
char	*remove_trailing_slash(const char *path)
{
	size_t	len = strlen(path);

	if (len > 1 && path[len - 1] == '/')
	{
		char *trimmed = strdup(path);
		trimmed[len - 1] = '\0';
		return trimmed;
	}
	return strdup(path);
}
int	cd(t_token *token, t_mini *mini)
{
	t_token	*current;
	int		mdr_args;
	char	*target;
	char	*pwd_current;
	char	*newpwd;
	char	*oldpwd;
	char	*cwd;

	// 💥 [NOUVEAU] Tester si le répertoire courant est encore valide
	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_putstr_fd("chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
	free(cwd);

	// Compter les arguments
	mdr_args = 1;
	current = token->next;
	while (current && current->type == ARG)
	{
		mdr_args++;
		current = current->next;
	}

	// Gérer trop d’arguments
	if (mdr_args > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}

	// Déterminer la cible
	if (mdr_args == 1)
	{
		target = get_value(mini->env, "HOME");
		if (!target)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	}
	else
	{
		if (token->next->str[0] == '-' && token->next->str[1])
			return cd_error(token);

		target = token->next->str;
		if (chdir(target) != 0)
			return cd_error(token);
	}

	// Sauvegarder OLDPWD
	oldpwd = get_value(mini->env, "PWD");
	if (oldpwd)
		update_or_add_var(mini, "OLDPWD", oldpwd);

	// Aller dans le répertoire (si ce n'était pas déjà fait)
	if (mdr_args == 1 && chdir(target) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}

	// On peut refaire un getcwd ici aussi, si nécessaire (facultatif)
	// cwd = getcwd(NULL, 0);
	// if (!cwd)
	// 	ft_putstr_fd("chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
	// free(cwd);

	// Mettre à jour PWD de façon logique (pas avec getcwd)
	char *logical_path;

	if (target[0] == '/')
		logical_path = strdup(target);
	else
	{
		pwd_current = get_value(mini->env, "PWD");
		if (!pwd_current)
			pwd_current = "";
		logical_path = concat_paths(pwd_current, target);
	}

	newpwd = remove_trailing_slash(logical_path);
	free(logical_path);
	update_or_add_var(mini, "PWD", newpwd);
	free(newpwd);

	return (0);
}