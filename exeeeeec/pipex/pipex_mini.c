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

#include "../../minishell.h"

static char	**token_to_cmd(t_token **current, t_mini *mini)
{
	t_token *start;
	int		count;
	char	**cmd;
	int		i;

	start = *current;
	count = 0;
	i = 0;
	while (*current && (*current)->type != PIPE)
	{
		if ((*current)->type == CMD || (*current)->type == ARG)
			count++;
		*current = (*current)->next;
	}
	cmd = rb_calloc(count + 1, sizeof(char *), mini->rb);
	if (!cmd)
		return (NULL);
	while (start && start->type != PIPE)
	{
		if (start->type == CMD || start->type == ARG)
		{
			cmd[i] = rb_strdup(start->str, mini->rb);
			i++;
		}
		start = start->next;
	}
	cmd[i] = NULL;
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

void	execute_pipeline(t_mini *mini)
{
	t_token	*current;
	t_pipex	pipex;
	int		status;

	current = mini->first;
	ft_bzero(&pipex, 0);
	pipex.cmd1 = token_to_cmd(&current, mini);
	if (current && current->type == PIPE)
		current = current->next;
	if (current)
		pipex.cmd2 = token_to_cmd(&current, mini);
	pipex.infile = STDIN_FILENO;
	pipex.outfile = STDOUT_FILENO;
	ft_pipex_loop(&pipex, mini->env);
	if (pipex.pid1 > 0)
		waitpid(pipex.pid1, &status, 0);
	if (pipex.pid2 > 0)
		waitpid(pipex.pid2, &status, 0);
}