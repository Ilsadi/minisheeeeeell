/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:44:26 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/12 23:26:19 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	restore_operators(char *str)
{
	int	i;
	
	i = 0;
	while (str && str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
}

int	parsing(char *str, t_mini *mini)
{
	t_token	*first;
	pid_t	pid;
	int status;
	int sig;

	if (!pars_quotes(str))
		return (0);
	if (!pars_pipe(str))
		return (0);
	if (!pars_redir(str))
		return (0);
	str = pars_expand(str, mini);
	restore_operators(str);
	// ft_printf("DEBUG: After pars_expand: '%s'\n", str);
	first = tokenize (str, mini);
	// ft_printlist(first);
	mini->first = first;
	if (first)
	{
		if (has_pipe(first))
		{
			execute_pipeline(mini);
			return (0);
		}
		if (!first || first->type != CMD)
			return (1);
		if (first->str ==NULL)
		{
			handle_redirections(first);
			return (0);
		}
		else if (is_builtins(first))
		{
			builtin_with_redir(first, mini);
			return (0);
		}
		pid = fork();
		if (pid == 0)
		{
			setup_child_signals();
			ft_commands(mini);
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			g_in_cmd = 1;
			waitpid(pid, &status, 0);
			g_in_cmd = 0;
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGINT)
					write(1, "\n", 1);
				else if (sig == SIGQUIT)
					write (1, "Quit (core dumped)\n", 20);
			}
		}
		return (0);
	}
	return (1);
}
