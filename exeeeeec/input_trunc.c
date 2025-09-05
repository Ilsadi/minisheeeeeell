/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:12:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/05 17:05:02 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	handle_redirections(t_token *tokens)
// {
// 	t_token	*current;
// 	int		fd;

// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == INPUT && current->next)
// 		{
// 			if (!current->next->str)
// 				return (-1);
// 			fd = open(current->next->str, O_RDONLY);
// 			if (fd < 0)
// 			{
// 				perror(current->next->str);
// 				return (-1);
// 			}
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 		current = current->next;
// 	}
// 	current = tokens;
// 	while (current)
// 	{	
// 		if (current->type == TRUNC && current->next)
// 		{
// 			fd = open(current->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 			if (fd < 0)
// 			{
// 				perror(current->next->str);
// 				return (-1);
// 			}
// 			dup2(STDOUT_FILENO, fd);
// 			close(fd);
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }
int	handle_redirections(t_token *tokens)
{
	t_token	*current;
	int		fd;
	int		pipefd[2];
	char	*line;
	int		last_heredoc_pipe = -1;

	current = tokens;
	while (current)
	{
		if (current->type == INPUT && current->next)
		{
			fd = open(current->next->str, O_RDONLY);
			if (fd < 0)
				return (perror(current->next->str), -1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (current->type == TRUNC && current->next)
		{
			fd = open(current->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(current->next->str), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (current->type == APPEND && current->next)
		{
			fd = open(current->next->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
				return (perror(current->next->str), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (current->type == HEREDOC && current->next)
		{
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
			if (last_heredoc_pipe != -1)
				close(last_heredoc_pipe);
			last_heredoc_pipe = pipefd[0];
		}
		current = current->next;
	}
	if (last_heredoc_pipe != -1)
	{
		dup2(last_heredoc_pipe, STDIN_FILENO);
		close (last_heredoc_pipe);
	}
	return (0);
}
