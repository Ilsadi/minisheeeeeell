/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:59:15 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/12 11:55:49 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	**unset_var(t_var **tab, char *name)
{
	t_var	**new_tab;
	int		i;
	int		is_found;

	i = 0;
	is_found = 0;
	new_tab = calloc(sizeof(t_var *), size_var(tab));
	if (!new_tab)
		return (NULL);
	while (tab[i])
	{
		if (ft_strcmp(name, tab[i]->name) == 0)
		{
			is_found = 1;
			free(tab[i]->name);
			free(tab[i]->value);
			free(tab[i]);
		}
		else
			new_tab[i - is_found] = tab[i];
		i++;
	}
	if (!is_found)
		return (free(new_tab), tab);
	return (free(tab), new_tab);
}

int	unset(t_token *token, t_mini *mini)
{
	t_token	*current;

	current = token->next;
	while (current && current->type == ARG)
	{
		mini->env = unset_var(mini->env, current->str);
		current = current->next;
	}
	return (0);
}

