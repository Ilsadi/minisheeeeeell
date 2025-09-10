/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:08:33 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/20 15:08:33 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_echo_n_flag(char *str)
{
	int	j;

	j = 2;
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[j] == 'n')
		j++;
	if (str[j] == '\0')
		return (1);
	return (0);
}

int	ft_echo(t_token *token)
{
	int		n_flag;
	t_token	*current;

	n_flag = 0;
	current = token->next;
	while (current && current->type == ARG && is_echo_n_flag(current->str))
	{
		n_flag = 1;
		current = current->next;
	}
	while (current && current->type == ARG)
	{
		ft_putstr_fd(current->str, 1);
		if (current->next && current->next->type == ARG)
			ft_putstr_fd(" ", 1);
		current = current->next;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

