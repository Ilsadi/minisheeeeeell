/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:04:13 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/08 20:24:40 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '|')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '|' || str[i] == '\0')
			{
				ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
				return (0);
			}
		}
		else
			i++;
	}
	return (1);
}
