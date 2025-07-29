/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:51:55 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/29 18:42:41 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	**created_tab(char **env)
{
	t_var	**tab;
	int		tablen;
	int		i;
	int		j;

	i = 0;
	tablen = size_tab(env);
	tab = ft_calloc(sizeof(t_var *), tablen + 1);
	if (!tab)
		return (NULL);

	while (env[i])
	{
		j = 0;
		tab[i] = malloc(sizeof(t_var));
		if (!tab[i])
		{
			destroy_tab(tab);
			return (NULL);
		}
		while (env[i][j] != '=')
			j++;
		tab[i]->name = ft_substr(env[i], 0, j);
		if (!tab[i]->name)
		{
			destroy_tab(tab);
			return (NULL);
		}
		tab[i]->value = ft_strdup(env[i] + (j + 1));
		if (!tab[i]->value)
		{
			destroy_tab(tab);
			return (NULL);
		}
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

