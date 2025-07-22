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

#include "../../minishell.h"

int	ft_echo(t_token *token)
{
	int		j;
	int		n_flag;
	t_token *current;

	n_flag = 0;
	current = token->next;

	while (current && current->type == ARG && current->str[0] == '-' && current->str[1] == 'n')
	{
		j = 2;
		while (current->str[j] == 'n')
			j++;
		if (current->str[j] != '\0')
			break ;
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

