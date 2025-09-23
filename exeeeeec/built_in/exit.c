/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:04:25 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/23 18:02:08 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	numeric_sign(const char *str, int *sign)
{
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		return (1);
	}
	*sign = 1;
	return (0);
}

static unsigned long long	numeric_limit(int sign)
{
	if (sign == -1)
		return ((unsigned long long)(-(LLONG_MIN + 1)) + 1);
	return (LLONG_MAX);
}

static int	numeric_check(const char *str, unsigned long long limit)
{
	unsigned long long	result;
	int					i;

	result = 0;
	i = 0;
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

int	is_numeric(char *str)
{
	int					i;
	int					sign;
	unsigned long long	limit;

	i = 0;
	if (!str || !*str)
		return (0);
	i += numeric_sign(str, &sign);
	if (!str[i])
		return (0);
	limit = numeric_limit(sign);
	return (numeric_check(str + i, limit));
}

static int	get_exit_code(t_token *arg, t_mini *mini)
{
	if (!arg || arg->type != ARG)
		return (mini->exit_status);
	if (!is_numeric(arg->str))
		return (print_exit_error(arg->str, 2));
	if (arg->next && arg->next->type == ARG)
		return (print_exit_error(NULL, 1));
	return (ft_atoi(arg->str));
}

int	print_exit_error(char *str, int code)
{
	if (code == 2)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (code == 1)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
	}
	return (code);
}

int	ft_exit(t_token *token, t_mini *mini)
{
	int	code;

	code = 0;
	if (!mini->in_pipeline)
		ft_printf("exit\n");
	code = get_exit_code(token->next, mini);
	if (mini->in_pipeline || code == 1)
		return (mini->exit_status = code % 256);
	rb_free_all(mini->rb);
	free(mini->rb);
	destroy_tab(mini->env);
	exit(code % 256);
}
