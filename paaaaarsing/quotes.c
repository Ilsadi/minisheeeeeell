/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:45:46 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/15 13:13:39 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	doubles_quotes_is_closed(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			flag++;
		i++;
	}
	if (flag % 2 == 0)
		return (0);
	else
		return (1);
}

int	quotes_is_closed(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			flag++;
		i++;
	}
	if (flag % 2 == 0)
		return (0);
	else
		return (1);
}
