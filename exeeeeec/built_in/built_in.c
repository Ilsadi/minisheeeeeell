/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:44:18 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/19 20:44:25 by cbrice           ###   ########.fr       */
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

static void	epurate(t_token **first)
{
	t_token	*current;
	t_token	*tmp;

	current = *first;
	while (current && current->type != CMD)
		current = current->next;
	*first = current;
	while (current->next && current->type != PIPE)
	{
		tmp = current->next;
		if (tmp->type >= HEREDOC)
		{
			current->next = tmp->next->next;
			continue ;
		}
		current = current->next;
	}
}

int	builtin_with_redir(t_token *first, t_mini *mini, t_pipex *p)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;
	(void)p;
	ret = 0;
	// ft_printlist(mini->first);
	if (ft_strcmp(first->str, "exit") == 0)
		ret = ft_exit(first, mini);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(first, -1) < 0)
		return (rb_free_all(mini->rb), free(mini->rb), exit(1), 1);
	epurate(&first);
	if (ft_strcmp(first->str, "env") == 0)
		ret = env(mini);
	else if (ft_strcmp(first->str, "export") == 0)
		ret = ft_export(first, mini);
	else if (ft_strcmp(first->str, "unset") == 0)
		ret = unset(first, mini);
	else if (ft_strcmp(first->str, "cd") == 0)
		ret = cd(first, mini->env);
	else if (ft_strcmp(first->str, "pwd") == 0)
		ret = pwd(first);
	else if (ft_strcmp(first->str, "echo") == 0)
		ret = ft_echo(first);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (ret);
}
