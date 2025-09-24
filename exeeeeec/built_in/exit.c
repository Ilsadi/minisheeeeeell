/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:04:25 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 17:59:09 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
