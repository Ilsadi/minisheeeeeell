/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:48:21 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 19:45:17 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_export_option(t_token *arg, t_mini *mini)
{
	char	*opt;
	int		ret;

	if (arg->str[0] == '-' && ft_strcmp(arg->str, "-p") != 0
		&& ft_strcmp(arg->str, "-f") != 0 && ft_strcmp(arg->str, "-n") != 0)
	{
		opt = ft_substr(arg->str, 0, 2);
		ret = export_option_error(opt, mini);
		free(opt);
		return (ret);
	}
	return (-1);
}

int	ft_export(t_token *token, t_mini *mini)
{
	t_token			*arg;
	t_export_ctx	ctx;
	int				ret;

	arg = token->next;
	ctx.status = 0;
	if (!arg || arg->type == PIPE)
	{
		print_export_env(mini->env, mini);
		return (0);
	}
	while (arg)
	{
		ret = handle_export_option(arg, mini);
		if (ret != -1)
			return (ret);
		ret = export_handle_arg(arg, mini, &ctx);
		if (ret)
			ctx.status = 1;
		arg = arg->next;
	}
	mini->exit_status = ctx.status;
	return (ctx.status);
}

