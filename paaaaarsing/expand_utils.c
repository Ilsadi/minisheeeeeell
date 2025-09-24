/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:58:24 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 20:12:56 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_no_var(t_exp *exp, char *str, t_mini *mini)
{
	char	*tmp;

	if (exp->start - 1 - exp->last_pos > 0)
	{
		tmp = rb_substr(str, exp->last_pos,
				exp->start - 1 - exp->last_pos, mini->rb);
		exp->result = rb_strfreejoin(exp->result, tmp, mini->rb);
	}
	tmp = rb_substr(str, exp->start - 1, 1, mini->rb);
	exp->result = rb_strfreejoin(exp->result, tmp, mini->rb);
}

void	expand_utils(t_exp *exp, t_mini *mini, char *str)
{
	int	i;

	i = -1;
	if (exp->i == exp->start)
	{
		dollar_no_var(exp, str, mini);
		exp->last_pos = exp->i;
		return ;
	}
	exp->tmp = rb_substr(str, exp->last_pos,
			exp->start - 1 - exp->last_pos, mini->rb);
	exp->result = rb_strfreejoin(exp->result, exp->tmp, mini->rb);
	exp->varname = rb_substr(str, exp->start, exp->i - exp->start, mini->rb);
	exp->tmp = get_value(mini->env, exp->varname);
	if (exp->tmp)
	{
		while (exp->tmp[++i])
			if (char_is_operator(exp->tmp[i]))
				exp->tmp[i] *= -1;
		exp->result = rb_strfreejoin(exp->result, exp->tmp, mini->rb);
	}
	exp->last_pos = exp->i;
}
