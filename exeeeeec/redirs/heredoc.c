/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:45:21 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/26 18:49:46 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	is_heredoc(int *pipefd, t_token *current, int *last_heredoc_pipe)
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
