/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/08/03 20:37:08 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/03 20:37:08 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd_args(t_token *start)
{
	t_token	*tmp;
	int		count;

	tmp = start;
	count = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (is_redir_token(tmp->type))
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		if (tmp->type == CMD || tmp->type == ARG)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	fill_cmd_args(char **cmd, t_token *start, t_mini *mini)
{
	t_token	*tmp;
	int		i;

	tmp = start;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (is_redir_token(tmp->type))
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		if (tmp->type == CMD || tmp->type == ARG)
			cmd[i++] = rb_strdup(tmp->str, mini->rb);
		tmp = tmp->next;
	}
	cmd[i] = NULL;
}

int	has_pipe(t_token *tokens)
{
	int	number;

	number = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			number += 1;
		tokens = tokens->next;
	}
	return (number);
}

static void	wait_pipeline(t_mini *mini, pid_t *tab_pid)
{
	int	i;

	i = 0;
	while (tab_pid[i])
	{
		waitpid(tab_pid[i], &mini->exit_status, 0);
		if (tab_pid[i + 1] == 0)
		{
			if (WIFEXITED(mini->exit_status))
				mini->exit_status = WEXITSTATUS(mini->exit_status);
			else if (WIFSIGNALED(mini->exit_status))
				mini->exit_status = 128 + WTERMSIG(mini->exit_status);
			else
				mini->exit_status = 1;
		}
		mini->exit_status = mini->exit_status % 256;
		i++;
	}
}

void	execute_pipeline(t_mini *mini, t_pipex *pipex)
{
	pid_t	*tab_pid;

	tab_pid = rb_calloc(has_pipe(mini->first) + 2, sizeof(pid_t), mini->rb);
	pipex->infile = STDIN_FILENO;
	pipex->outfile = STDOUT_FILENO;
	if (mini->first && mini->first->type == PIPE)
		mini->first = mini->first->next;
	mini->in_pipeline = 1;
	ft_pipex_loop(pipex, mini->first, mini, tab_pid);
	mini->in_pipeline = 0;
	wait_pipeline(mini, tab_pid);
}
