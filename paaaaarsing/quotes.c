/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:45:46 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/23 17:38:23 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_is_operator(char c)
{
	if (c == '<' || c == '>')
		return (1);
	else if (c == '|')
		return (1);
	return (0);
}

int	pars_quotes(char *str)
{
	int	i;
	int	state;

	state = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && state == 0)
			state = 1;
		else if (str[i] == '"' && state == 1)
			state = 0;
		else if (str[i] == '\'' && state == 0)
			state = 2;
		else if (str[i] == '\'' && state == 2)
			state = 0;
		else if (state == 1 && char_is_operator(str[i]))
			str[i] *= -1;
		i++;
	}
	if (state != 0)
		return (0);
	return (1);
}

