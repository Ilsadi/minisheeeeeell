/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:04:25 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/10 15:43:26 by ilsadi           ###   ########.fr       */
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


int	ft_exit(t_token *token, t_mini *mini)
{
	int		code;
	t_token	*arg;

	arg = token->next;
	ft_printf("exit\n");
	if (!arg || arg->type != ARG)
		code = 0;
	else if (!is_numeric(arg->str))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		code = 2;
	}
	else if (arg->next && arg->next->type == ARG)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		code = 1;
	}
	else
		code = ft_atoi(arg->str);
	rb_free_all(mini->rb);
	free(mini->rb);
	destroy_tab(mini->env, NULL);
	exit(code & 255);
}
