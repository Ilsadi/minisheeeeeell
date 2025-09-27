/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:51:55 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/27 16:46:33 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	*var_from_env(const char *entry)
{
	char	*eq;
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	eq = ft_strchr(entry, '=');
	if (!eq)
		return (free(var), NULL);
	var->name = ft_substr(entry, 0, eq - entry);
	if (!var->name)
		return (free(var), NULL);
	var->value = ft_strdup(eq + 1);
	if (!var->value)
	{
		free(var->name);
		free(var);
		return (NULL);
	}
	return (var);
}

t_var	**created_tab(char **env)
{
	t_var	**tab;
	int		tablen;
	int		i;

	tablen = size_tab(env);
	tab = ft_calloc(sizeof(t_var *), tablen + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (env[i])
	{
		tab[i] = var_from_env(env[i]);
		if (!tab[i])
			return (destroy_tab(tab), NULL);
		i++;
	}
	return (tab);
}

char	*get_value(t_var **tab, char *name)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(name, tab[i]->name) == 0)
		{
			return (tab[i]->value);
		}
		i++;
	}
	return (NULL);
}

void	destroy_tab(t_var **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]->name);
		free(tab[i]->value);
		free(tab[i]);
		i++;
	}
	free(tab);
}
