/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:37:08 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/03 20:37:08 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir_token(int type)
{
	return (type == INPUT || type == TRUNC
		|| type == APPEND || type == HEREDOC);
}

static int	count_cmd_args(t_token *start)
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

static void	fill_cmd_args(char **cmd, t_token *start, t_mini *mini)
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

char	**token_to_cmd(t_token **current, t_mini *mini)
{
	t_token	*start;
	int		count;
	char	**cmd;

	start = *current;
	count = count_cmd_args(start);
	cmd = rb_calloc(count + 1, sizeof(char *), mini->rb);
	if (!cmd)
		return (NULL);
	fill_cmd_args(cmd, start, mini);
	while (*current && (*current)->type != PIPE)
		*current = (*current)->next;
	return (cmd);
}

int	has_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == PIPE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

static int	wait_pipeline(void)
{
	int		status;
	int		last_status;
	pid_t	waited_pid;

	last_status = 0;
	waited_pid = 0;
	while (1)
	{
		waited_pid = wait(&status);
		if (waited_pid <= 0)
			break ;
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}
	return (last_status);
}

void	execute_pipeline(t_mini *mini)
{
	t_pipex	pipex;

	ft_memset(&pipex, 0, sizeof(t_pipex));
	pipex.infile = STDIN_FILENO;
	pipex.outfile = STDOUT_FILENO;
	if (mini->first && mini->first->type == PIPE)
		mini->first = mini->first->next;
	ft_pipex_loop(&pipex, mini->first, mini);
	mini->exit_status = wait_pipeline();
}
