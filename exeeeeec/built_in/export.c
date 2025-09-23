/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:48:21 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/23 20:07:01 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_swap_var(t_var **a, t_var **b)
{
	t_var	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_var	**add_var(t_var **tab, t_var *new_var)
{
	t_var	**new_tab;
	int		i;
	int		size;

	size = size_var(tab);
	new_tab = malloc(sizeof(t_var *) * (size + 2));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = new_var;
	new_tab[i + 1] = NULL;
	free(tab);
	return (new_tab);
}

static void	ft_sort_tab(t_var ***tab)
{
	int		i;
	int		j;
	int		len;
	t_var	**tmp;

	len = size_var(*tab);
	tmp = *tab;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(tmp[j]->name, tmp[j + 1]->name) > 0)
			{
				ft_swap_var(&(tmp[j]), &(tmp[j + 1]));
			}
			j++;
		}
		i++;
	}
}

void	print_export_env(t_var **env, t_mini *mini)
{
	int		i;
	t_var	**tmp;

	i = 0;
	tmp = rb_calloc(sizeof(t_var *), (size_var(env) + 1), mini->rb);
	while (env[i])
	{
		tmp[i] = env[i];
		i++;
	}
	i = 0;
	ft_sort_tab(&tmp);
	while (tmp[i])
	{
		ft_printf("export %s", tmp[i]->name);
		if (tmp[i]->value)
			ft_printf("=\"%s\"", tmp[i]->value);
		ft_printf("\n");
		i++;
	}
}

void	update_or_add_var(t_mini *mini, char *name, char *value)
{
	int		i;
	t_var	*new_var;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strcmp(mini->env[i]->name, name) == 0)
		{
			free(mini->env[i]->value);
			mini->env[i]->value = ft_strdup(value);
			return ;
		}
		i++;
	}
	new_var = malloc(sizeof(t_var));
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(value);
	mini->env = add_var(mini->env, new_var);
}

static void	add_var_no_value(t_mini *mini, char *name)
{
	t_var	*new_var;

	new_var = malloc(sizeof(t_var));
	new_var->name = ft_strdup(name);
	new_var->value = NULL;
	mini->env = add_var(mini->env, new_var);
}

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


static int	export_option_error(char *str, t_mini *mini)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("export: usage: export [-fn] "
		"[name[=value] ...] or export -p\n", 2);
	mini->exit_status = 2;
	return (2);
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

static int	export_handle_arg(t_token *arg, t_mini *mini, t_export_ctx *ctx)
{
	ctx->equal_pos = ft_strchr(arg->str, '=');
	if (ctx->equal_pos)
		return (export_assign(arg, mini, ctx));
	return (export_no_assign(arg, mini, ctx));
}

int	ft_export(t_token *token, t_mini *mini)
{
	t_token			*arg;
	t_export_ctx	ctx;
	int				ret;
	char			*opt;

	arg = token->next;
	ctx.status = 0;
	if (!arg || arg->type == PIPE)
		return (print_export_env(mini->env, mini), 0);
	while (arg)
	{
		if (arg->str[0] == '-' && ft_strcmp(arg->str, "-p") != 0
			&& ft_strcmp(arg->str, "-f") != 0 && ft_strcmp(arg->str, "-n") != 0)
		{
			opt = ft_substr(arg->str, 0, 2);
			ret = export_option_error(opt, mini);
			free(opt);
			return (ret);
		}
		ctx.status = export_handle_arg(arg, mini, &ctx) || ctx.status;
		arg = arg->next;
	}
	mini->exit_status = ctx.status;
	return (ctx.status);
}

