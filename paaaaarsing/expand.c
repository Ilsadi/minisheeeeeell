/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:52:04 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/14 01:20:40 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_no_var(char **result, const char *str,
	int last_pos, int start, t_mini *mini)
{
	char	*tmp;

	if (start - 1 - last_pos > 0)
	{
		tmp = rb_substr(str, last_pos, start - 1 - last_pos, mini->rb);
		*result = rb_strfreejoin(*result, tmp, mini->rb);
	}
	tmp = rb_substr(str, start - 1, 1, mini->rb);
	*result = rb_strfreejoin(*result, tmp, mini->rb);
}

char	*pars_expand(char *str, t_mini *mini)
{
	int		i;
	int		start;
	char	*varname;
	char	*result;
	char	*tmp;
	int		last_pos;
	int		state;

	i = 0;
	last_pos = 0;
	state = 0;
	result = rb_strdup("", mini->rb);
	while (str[i])
	{
		if (str[i] == '"' && state == 0)
			state = 1;
		else if (str[i] == '"' && state == 1)
			state = 0;
		else if (str[i] == '\'' && state == 0)
			state = 2;
		else if (str[i] == '\'' && state == 2)
			state = 0;
		if (str[i] == '$' && state != 2)
		{
			if (str[i + 1] == '?')
			{
				tmp = rb_substr(str, last_pos, i - last_pos, mini->rb);
				result = rb_strfreejoin(result, tmp, mini->rb);
				tmp = rb_itoa(mini->exit_status, mini->rb); // ← plus de division ici !
				result = rb_strfreejoin(result, tmp, mini->rb);
				last_pos = i + 2;
				i += 2;
				continue ;
			}
			i++;
			start = i;
			if (!ft_isalpha(str[i]) && str[i] != '_')
			{
				if (ft_isdigit(str[i]) || ((str[i] == '\'' || str[i] == '"') && state < 1))
					tmp = rb_substr(str, last_pos, start - 1 - last_pos, mini->rb);
				else
					tmp = rb_substr(str, last_pos, start - last_pos, mini->rb);
				result = rb_strfreejoin(result, tmp, mini->rb);
				i += ft_isdigit(str[i]);
				last_pos = i;
				continue ;
			}
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			if (i == start)
			{
				dollar_no_var(&result, str, last_pos, start, mini);
				last_pos = i;
				continue ;
			}
			tmp = rb_substr(str, last_pos, start - 1 - last_pos, mini->rb);
			result = rb_strfreejoin(result, tmp, mini->rb);
			varname = rb_substr(str, start, i - start, mini->rb);
			tmp = get_value(mini->env, varname);
			if (tmp)
				result = rb_strfreejoin(result, tmp, mini->rb);
			last_pos = i;
			continue ;
		}
		i++;
	}
	tmp = rb_substr(str, last_pos, ft_strlen(str) - last_pos, mini->rb);
	result = rb_strfreejoin(result, tmp, mini->rb);
	return (result);
}
