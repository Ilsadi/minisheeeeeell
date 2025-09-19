/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:04:25 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/19 20:51:43 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_numeric(char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;
	unsigned long long	limit;

	if (!str || !*str)
		return (0);

	i = 0;
	sign = 1;
	result = 0;

	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}

	if (!str[i])
		return (0);

	if (sign == -1)
		limit = (unsigned long long)(-(LLONG_MIN + 1)) + 1;
	else
		limit = LLONG_MAX;

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);

		result = result * 10 + (str[i] - '0');

		if (result > limit)
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
	if (!mini->in_pipeline)
		ft_printf("exit\n");
	// ft_printf("je suis dans le 1\n");
	if (!arg || arg->type != ARG)
		code = mini->exit_status;
	else if (!is_numeric(arg->str))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		code = 2;
		// return (mini->exit_status = 2);
	}
	else if (arg->next && arg->next->type == ARG)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (mini->exit_status = 1);
	}
	else
		code = ft_atoi(arg->str);
		
	if (mini->in_pipeline)
		return code % 256;	
	
	rb_free_all(mini->rb);
	free(mini->rb);
	destroy_tab(mini->env);
	exit(code % 256);
}
