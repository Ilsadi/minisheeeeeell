/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:12:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/27 19:59:39 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_redir(t_token *current, int pipefd[2],
		int *last_heredoc_pipe)
{
	if (current->type == INPUT && current->next)
		return (is_input(current));
	if (current->type == TRUNC && current->next)
		return (is_trunc(current));
	if (current->type == APPEND && current->next)
		return (is_append(current));
	if (current->type == HEREDOC && current->next)
		return (is_heredoc(pipefd, current, last_heredoc_pipe));
	return (0);
}

int	handle_redirections(t_token *tokens, int stop)
{
	t_token	*current;
	int		status;
	int		pipefd[2];
	int		last_heredoc_pipe;

	current = tokens;
	status = 0;
	last_heredoc_pipe = -1;
	while (current && current->type != stop)
	{
		status = process_redir(current, pipefd, &last_heredoc_pipe);
		if (status < 0)
			return (-1);
		current = current->next;
	}
	if (last_heredoc_pipe != -1)
	{
		dup2(last_heredoc_pipe, STDIN_FILENO);
		close(last_heredoc_pipe);
	}
	return (0);
}
