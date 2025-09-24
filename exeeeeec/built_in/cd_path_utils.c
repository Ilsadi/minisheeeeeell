/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:15:31 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 17:59:05 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_paths(const char *base, const char *sub)
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

char	*build_logical_path(char *target, t_mini *mini)
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
