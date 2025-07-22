/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:44:26 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/22 15:06:42 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->str);
		free(token);
		token = tmp;
	}
}

int	parsing(char *str, char **envp)
{
	t_token	*first;

	if (!pars_quotes(str))
		return (0);
	if (!pars_slash(str))
		return (0);
	if (!pars_pipe(str))
		return (0);
	if (!pars_redir(str))
		return (0);
	str = pars_expand(str, envp);
	first = tokenize (str);
	if (first)
	{
		if (is_builtin(first->str))
			ft_printf("Built-in detected: %s\n", first->str);
		else
			ft_printf("Not a built-in: %s\n", first->str);
	}
	else
		ft_printf("No tokens created\n");
	ft_printlist(first);
	free_token_list(first);
	free(str);
	return (1);
}

void	ft_printlist(t_token *token)
{
	while (token)
	{
		ft_printf("%d ", token->type);
		if (token->str)
			ft_printf("%s ", token->str);
		if (token->next)
			ft_printf("-> ");
		else
			ft_printf("\n");
		token = token->next;
	}
}