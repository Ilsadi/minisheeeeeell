/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:48:21 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/10 12:08:36 by ilsadi           ###   ########.fr       */
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

static void	print_export_env(t_var **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("export %s", env[i]->name);
		if (env[i]->value)
			ft_printf("=\"%s\"", env[i]->value);
		ft_printf("\n");
		i++;
	}
}

static void	update_or_add_var(t_mini *mini, char *name, char *value)
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

static void	add_var_no_value(t_mini *mini, char *name)
{
	t_var	*new_var;

	new_var = malloc(sizeof(t_var));
	new_var->name = ft_strdup(name);
	new_var->value = NULL;
	mini->env = add_var(mini->env, new_var);
}

int	ft_export(t_token *token, t_mini *mini)
{
	char	*equal_pos;
	char	*name;
	char	*value;

	if (!token->next)
	{
		print_export_env(mini->env);
		return (0);
	}
	equal_pos = ft_strchr(token->next->str, '=');
	if (equal_pos)
	{
		name = ft_substr(token->next->str, 0, equal_pos - token->next->str);
		value = equal_pos + 1;
		update_or_add_var(mini, name, value);
		free(name);
	}
	else
	{
		name = ft_strdup(token->next->str);
		add_var_no_value(mini, name);
		free(name);
	}
	return (0);
}
