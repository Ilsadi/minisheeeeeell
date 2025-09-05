/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:44:18 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/05 17:29:24 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(t_token *first)
{
	if (!first || !first->str)
		return (0);
	if (ft_strcmp(first->str, "env") == 0)
		return (1);
	else if (ft_strcmp(first->str, "export") == 0)
		return (1);
	else if (ft_strcmp(first->str, "exit") == 0)
		return (1);
	else if (ft_strcmp(first->str, "unset") == 0)
		return (1);
	else if (ft_strcmp(first->str, "cd") == 0)
		return (1);
	else if (ft_strcmp(first->str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(first->str, "echo") == 0)
		return (1);
	return (0);
}

int	builtin_with_redir(t_token *first, t_mini *mini)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	handle_redirections(first);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	if (ft_strcmp(first->str, "env") == 0)
		env(mini->env);
	else if (ft_strcmp(first->str, "export") == 0)
		ft_export(first, mini);
	else if (ft_strcmp(first->str, "exit") == 0)
		ft_exit(first, mini);
	else if (ft_strcmp(first->str, "unset") == 0)
		unset(first, mini);
	else if (ft_strcmp(first->str, "cd") == 0)
		cd(first, mini->env);
	else if (ft_strcmp(first->str, "pwd") == 0)
		pwd();
	else if (ft_strcmp(first->str, "echo") == 0)
		ft_echo(first);

	return (0);
}
