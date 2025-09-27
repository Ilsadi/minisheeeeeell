/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:21:07 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/27 16:47:04 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	**add_var(t_var **tab, t_var *new_var)
{
	t_var	**new_tab;
	int		i;
	int		size;

	size = size_var(tab);
	new_tab = malloc(sizeof(t_var *) * (size + 2));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = new_var;
	new_tab[i + 1] = NULL;
	free(tab);
	return (new_tab);
}

void	update_or_add_var(t_mini *mini, char *name, char *value)
{
	int		i;
	t_var	*new_var;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strcmp(mini->env[i]->name, name) == 0)
		{
			free(mini->env[i]->value);
			mini->env[i]->value = ft_strdup(value);
			return ;
		}
		i++;
	}
	new_var = malloc(sizeof(t_var));
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(value);
	mini->env = add_var(mini->env, new_var);
}

void	add_var_no_value(t_mini *mini, char *name)
{
	t_var	*new_var;

	new_var = malloc(sizeof(t_var));
	new_var->name = ft_strdup(name);
	new_var->value = NULL;
	mini->env = add_var(mini->env, new_var);
}
