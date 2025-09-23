/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:34:11 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/23 21:23:55 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(int type)
{
	return (type == INPUT || type == TRUNC || type == APPEND
		|| type == HEREDOC);
}

char	**token_to_cmd(t_token **current, t_mini *mini)
{
	t_token	*start;
	int		count;
	char	**cmd;

	start = *current;
	count = count_cmd_args(start);
	cmd = rb_calloc(count + 1, sizeof(char *), mini->rb);
	if (!cmd)
		return (NULL);
	fill_cmd_args(cmd, start, mini);
	while (*current && (*current)->type != PIPE)
		*current = (*current)->next;
	return (cmd);
}

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

static	char	*handle_path_cmd(char *cmd, t_mini *mini)
{
	if (access(cmd, F_OK) == 0)
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
