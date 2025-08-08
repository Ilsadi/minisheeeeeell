/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:48:21 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/04 15:01:27 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static t_var	**add_var(t_var **tab, t_var *new_var)
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

int	ft_export(t_token *token, t_mini *mini)
{
	char	*equal_pos;
	int		i;
	char	*name;
	char	*value;
	t_var	*new_var;

	if (!token->next)
	{
		i = 0;
		while (mini->env[i])
		{
			
			ft_printf("declare -x %s", mini->env[i]->name); // a verifier
			if (mini->env[i]->value)
				ft_printf("=\"%s\"", mini->env[i]->value);
			ft_printf("\n");
			i++;
		}
		return (0);
	}
	equal_pos = ft_strchr(token->next->str, '=');
	if (equal_pos)
	{
		name = ft_substr(token->next->str, 0, equal_pos - token->next->str);
		value = equal_pos + 1;
		i = 0;
		while (mini->env[i])
		{
			if (ft_strcmp(mini->env[i]->name, name) == 0)
			{
				free(mini->env[i]->value);
				mini->env[i]->value = ft_strdup(value);
				free(name);
				return (0);
			}
			i++;
		}
		new_var = malloc(sizeof(t_var));
		new_var->name = ft_strdup(name);
		new_var->value = ft_strdup(value);
		free(name);
		mini->env = add_var(mini->env, new_var);
	}
	else
	{
		name = ft_strdup(token->next->str);
		new_var = malloc(sizeof(t_var));
		new_var->name = ft_strdup(name);
		new_var->value = NULL;
		free(name);
		mini->env = add_var(mini->env, new_var);
	}
	return (0);
}
