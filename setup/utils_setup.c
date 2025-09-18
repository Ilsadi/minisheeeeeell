/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:02:04 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/18 17:45:26 by cbrice           ###   ########.fr       */
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
		if (tab[i]->value)
			ft_printf("%s=%s\n", tab[i]->name, tab[i]->value);
		i++;
	}
}

// void	ft_sort_tab(t_var ***tab)
// {
// 	int i;
// 	int j;
// 	int len;

// 	len = size_var(*tab);
// 	i = 0;
// 	while(i < len - 1)
// 	{
// 		j = 0;
// 		while(j < len - i - 1)
// 		{
// 			if (*tab[j] > *tab[j + 1])
// 				ft_swap_var(&*tab[j], &*tab[j + 1]);
// 			j++;
// 		}
// 		i++;
// 	}
// }

