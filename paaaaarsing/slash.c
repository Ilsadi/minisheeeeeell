/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:20:19 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/21 14:30:16 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_word(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '.');
}

int	pars_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			if (i == 0)
			{
				if (!is_word(str[i + 1]))
				{
					ft_putstr_fd(ERROR_ENEXPECTED_SLASH, 2);
					return (0);
				}
				i++;
				continue ;
			}
			if (!is_word(str[i - 1]) || !is_word(str[i + 1]))
			{
				ft_putstr_fd(ERROR_ENEXPECTED_SLASH, 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

