/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:04:25 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/01 16:44:51 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_numeric(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_token *token, t_var **var)
{	
	t_token	*current;
	int		exit_code;

	current = token->next;

	if (!current || current->type != ARG)
	{
		ft_printf("exit\n");
		free_token_list(token);
		destroy_tab(var);
		exit(0);
	}
	exit_code = ft_atoi(current->str);
	if (current->next && current->next->type == ARG)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (!is_numeric(current->str))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		free_token_list(token);
		destroy_tab(var);
		exit(2);
	}
	free_token_list(token);
	destroy_tab(var);
	//clear_history();
	ft_printf("exit\n");
	exit(exit_code & 255);
}