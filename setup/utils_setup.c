/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:02:04 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/05 17:26:10 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_tab(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		i++;
	}
	return (i);
}

int	size_var(t_var **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}

void	print_tab(t_var **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s=%s\n", tab[i]->name, tab[i]->value);
		i++;
	}
}
