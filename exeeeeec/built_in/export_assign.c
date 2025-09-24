/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_assign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:22:20 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 17:59:09 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	vakud_bane(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (i == 0 && !ft_isalpha(name[i]) && name[i] != '_')
			return (0);
		else if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (i > 0);
}

static int	export_invalid_identifier(char *str)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	export_assign(t_token *arg, t_mini *mini, t_export_ctx *ctx)
{
	int	ret;

	ctx->name = ft_substr(arg->str, 0, ctx->equal_pos - arg->str);
	if (!vakud_bane(ctx->name))
	{
		ret = export_invalid_identifier(arg->str);
		free(ctx->name);
		return (ret);
	}
	ctx->value = ctx->equal_pos + 1;
	update_or_add_var(mini, ctx->name, ctx->value);
	free(ctx->name);
	return (0);
}

static int	export_no_assign(t_token *arg, t_mini *mini, t_export_ctx *ctx)
{
	int	ret;

	ctx->name = ft_strdup(arg->str);
	if (!vakud_bane(ctx->name))
	{
		ret = export_invalid_identifier(arg->str);
		free(ctx->name);
		return (ret);
	}
	add_var_no_value(mini, ctx->name);
	free(ctx->name);
	return (0);
}

int	export_handle_arg(t_token *arg, t_mini *mini, t_export_ctx *ctx)
{
	ctx->equal_pos = ft_strchr(arg->str, '=');
	if (ctx->equal_pos)
		return (export_assign(arg, mini, ctx));
	return (export_no_assign(arg, mini, ctx));
}
