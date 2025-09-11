/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:34:11 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/11 18:30:42 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_cmd_in_paths(char **paths, char *cmd, t_mini *mini)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		tmp = rb_strfreejoin(paths[i], "/", mini->rb);
		full_path = rb_strfreejoin(tmp, cmd, mini->rb);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

static char	*handle_path_cmd(char *cmd,t_mini *mini)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (rb_strdup(cmd, mini->rb));
	return (NULL);
}

char	*find_cmd_path(char *cmd, t_mini *mini)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	if (ft_strchr(cmd, '/'))
		return (handle_path_cmd(cmd, mini));
	if (!*cmd)
		return (NULL);
	path_env = get_value(mini->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = rb_split(path_env, ':', mini->rb);
	if (!paths)
		return (NULL);
	full_path = find_cmd_in_paths(paths, cmd, mini);
	return (full_path);
}
