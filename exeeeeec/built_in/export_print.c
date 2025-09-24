/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:20:12 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 17:59:09 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_swap_var(t_var **a, t_var **b)
{
	t_var	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	ft_sort_tab(t_var ***tab)
{
	int		i;
	int		j;
	int		len;
	t_var	**tmp;

	len = size_var(*tab);
	tmp = *tab;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(tmp[j]->name, tmp[j + 1]->name) > 0)
				ft_swap_var(&(tmp[j]), &(tmp[j + 1]));
			j++;
		}
		i++;
	}
}

void	print_export_env(t_var **env, t_mini *mini)
{
	int		i;
	t_var	**tmp;

	i = 0;
	tmp = rb_calloc(sizeof(t_var *), (size_var(env) + 1), mini->rb);
	while (env[i])
	{
		tmp[i] = env[i];
		i++;
	}
	i = 0;
	ft_sort_tab(&tmp);
	while (tmp[i])
	{
		ft_printf("export %s", tmp[i]->name);
		if (tmp[i]->value)
			ft_printf("=\"%s\"", tmp[i]->value);
		ft_printf("\n");
		i++;
	}
}
