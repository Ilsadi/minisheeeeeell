/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:44:26 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/01 16:46:25 by ilsadi           ###   ########.fr       */
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

int	parsing(char *str, t_mini *mini)
{
	t_token	*first;
	char	*original_str;

	if (!pars_quotes(str))
		return (0);
	// if (!pars_slash(str))
	// 	return (0);
	if (!pars_pipe(str))
		return (0);
	if (!pars_redir(str))
		return (0);
	original_str = str;
	str = pars_expand(str, mini->env);
	first = tokenize (str);
	if (first)
	{
		if (ft_strcmp(first->str, "echo") == 0)
			ft_echo(first);
		else if (ft_strcmp(first->str, "pwd") == 0)
			pwd();
		else if (ft_strcmp(first->str, "env") == 0)
			env(mini->env);
		else if (ft_strcmp(first->str, "cd") == 0)
			cd(first, mini->env);
		else if (ft_strcmp(first->str, "exit") == 0)
		{
			free(str);
			ft_exit(first, mini->env);
		}
		else if (ft_strcmp(first->str, "unset") == 0)
			unset(first, mini);
		// elsef
		// 	ft_printf("Not a built-in: %s\n", first->str);
	}
	else
		// ft_printf("No tokens created\n");
	// ft_printlist(first);
	 if (str != original_str)
		free(str);
	free_token_list(first);
	free(str);
	// printf("teeeeeeeeeeeeeeeeeest\n");
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
