/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:44:26 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/27 20:29:03 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_no_fork_cases(t_token *first, t_mini *mini, t_pipex *p)
{
	if (has_pipe(first))
	{
		execute_pipeline(mini, p);
		return (1);
	}
	if (is_builtins(first))
	{
		mini->exit_status = builtin_with_redir(first, mini, p);
		return (1);
	}
	return (0);
}

static int	parsing_prepare(char **str, t_token **first, t_mini *mini)
{
	*str = prepare_input(*str, mini);
	if (!*str)
		return (0);
	*first = build_tokens(*str, mini);
	if (!*first)
	{
		mini->first = NULL;
		return (0);
	}
	mini->first = *first;
	return (1);
}

static void	parsing_fork_and_run(t_token *first, t_mini *mini)
{
	pid_t	pid;
	int		fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	if (handle_redirections(first, -1) < 0)
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		mini->exit_status = 1;
		return ;
	}
	pid = fork();
	if (pid == 0)
		run_child_branch(mini);
	else if (pid > 0)
		run_parent_branch(mini, pid);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void	parsing(char *str, t_mini *mini, t_pipex *p)
{
	t_token	*first;

	first = NULL;
	if (!parsing_prepare(&str, &first, mini))
		return ;
	if (handle_no_fork_cases(first, mini, p))
		return ;
	parsing_fork_and_run(first, mini);
}
