/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:12:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 14:58:11 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_input(t_token *current)
{
	int	fd;

	fd = open(current->next->str, O_RDONLY);
	if (fd < 0)
		return (perror(current->next->str), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

static int	is_trunc(t_token *current)
{
	int	fd;

	fd = open(current->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(current->next->str), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	is_append(t_token *current)
{
	int	fd;

	fd = open(current->next->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (perror(current->next->str), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	is_heredoc(int *pipefd, t_token *current, int *last_heredoc_pipe)
{
	char	*line;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, current->next->str) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	if (*last_heredoc_pipe != -1)
		close(*last_heredoc_pipe);
	*last_heredoc_pipe = pipefd[0];
	return (1);
}

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
