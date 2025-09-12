/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ampersand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:36:11 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/12 11:55:25 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_ampersand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '&' && str[i + 1] == '&')
		{
			ft_error("syntax error near unexpected token `&&'\n");
			return (0);
		}
		else if (str[i] == '&')
		{
			ft_error("syntax error near unexpected token `&&'\n");
			return (0);
		}
		i++;
	}
	return (1);
}
