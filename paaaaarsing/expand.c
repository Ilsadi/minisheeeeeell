/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:52:04 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 20:13:13 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quotes_exp(t_exp *exp, char c)
{
	if (c == '"' && exp->state == 0)
		exp->state = 1;
	else if (c == '"' && exp->state == 1)
		exp->state = 0;
	else if (c == '\'' && exp->state == 0)
		exp->state = 2;
	else if (c == '\'' && exp->state == 2)
		exp->state = 0;
}

static int	is_interro(t_exp *exp, char *str, t_mini *mini)
{
	if (str[exp->i + 1] == '?')
	{
		exp->tmp = rb_substr(str, exp->last_pos,
				exp->i - exp->last_pos, mini->rb);
		exp->result = rb_strfreejoin(exp->result, exp->tmp, mini->rb);
		exp->tmp = rb_itoa(mini->exit_status, mini->rb);
		exp->result = rb_strfreejoin(exp->result, exp->tmp, mini->rb);
		exp->last_pos = exp->i + 2;
		exp->i += 2;
		return (1);
	}
	exp->i++;
	exp->start = exp->i;
	return (0);
}

static int	expand_invalid_name(t_exp *exp, char *str, t_mini *mini)
{
	if (!ft_isalpha(str[exp->i]) && str[exp->i] != '_')
	{
		if (ft_isdigit(str[exp->i]) || ((str[exp->i] == '\''
					|| str[exp->i] == '"') && exp->state < 1))
			exp->tmp = rb_substr(str, exp->last_pos,
					exp->start - 1 - exp->last_pos, mini->rb);
		else
			exp->tmp = rb_substr(str, exp->last_pos,
					exp->start - exp->last_pos, mini->rb);
		exp->result = rb_strfreejoin(exp->result, exp->tmp, mini->rb);
		exp->i += ft_isdigit(str[exp->i]);
		exp->last_pos = exp->i;
		return (1);
	}
	return (0);
}

char	*pars_expand(char *str, t_mini *mini)
{
	t_exp	exp;

	ft_bzero(&exp, sizeof(t_exp));
	exp.result = rb_strdup("", mini->rb);
	while (str[exp.i])
	{
		quotes_exp(&exp, str[exp.i]);
		if (str[exp.i] == '$' && exp.state != 2)
		{
			if (is_interro(&exp, str, mini))
				continue ;
			if (expand_invalid_name(&exp, str, mini))
				continue ;
			while (ft_isalnum(str[exp.i]) || str[exp.i] == '_')
				exp.i++;
			expand_utils(&exp, mini, str);
			continue ;
		}
		exp.i++;
	}
	exp.tmp = rb_substr(str, exp.last_pos,
			ft_strlen(str) - exp.last_pos, mini->rb);
	exp.result = rb_strfreejoin(exp.result, exp.tmp, mini->rb);
	return (exp.result);
}
