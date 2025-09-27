/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:45:21 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/27 19:57:36 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc_loop(int *pipefd, t_token *current, int *last_pipe)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_state == STATE_SIGINT)
			return (free(line), handle_heredoc_interrupt(pipefd, last_pipe));
		if (ft_strcmp(line, current->next->str) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	return (0);
}

int	is_heredoc(int *pipefd, t_token *current, int *last_heredoc_pipe)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	setup_heredoc_signals();
	if (read_heredoc_loop(pipefd, current, last_heredoc_pipe) == -2)
		return (-2);
	close(pipefd[1]);
	if (*last_heredoc_pipe != -1)
		close(*last_heredoc_pipe);
	*last_heredoc_pipe = pipefd[0];
	g_state = STATE_IDLE;
	setup_child_signals();
	return (1);
}
