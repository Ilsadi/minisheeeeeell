/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:04:13 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/17 12:29:25 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
