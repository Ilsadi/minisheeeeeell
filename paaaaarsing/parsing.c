/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:44:26 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/03 18:06:29 by ilsadi           ###   ########.fr       */
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

int	parsing(char *str, t_mini *mini)
{
	t_token	*first;

	if (!pars_quotes(str))
		return (0);
	// if (!pars_slash(str))
	// 	return (0);
	if (!pars_pipe(str))
		return (0);
	if (!pars_redir(str))
		return (0);
	str = pars_expand(str, mini);
	first = tokenize (str, mini);
	// ft_printlist(first);
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
			int exit_code = 0;
    		if (first->next && first->next->type == ARG)
        		exit_code = ft_atoi(first->next->str);
    		rb_free_all(mini->rb);
			free(mini->rb);
			destroy_tab(mini->env);
    		ft_printf("exit\n");
    		exit(exit_code & 255);
		}
		else if (ft_strcmp(first->str, "unset") == 0)
			unset(first, mini);
		else if (ft_strcmp(first->str, "export") == 0)
			ft_export(first, mini);
		// elsef
		// 	ft_printf("Not a built-in: %s\n", first->str);
	}
	rb_free_all(mini->rb);
	return (1);
}


