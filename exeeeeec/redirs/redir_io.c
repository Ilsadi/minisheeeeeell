/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:44:35 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/27 19:48:56 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	is_input(t_token *current)
{
	int	fd;

	fd = open(current->next->str, O_RDONLY);
	if (fd < 0)
		return (perror(current->next->str), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	is_trunc(t_token *current)
{
	int	fd;

	fd = open(current->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(current->next->str), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	is_append(t_token *current)
{
	int	fd;

	fd = open(current->next->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (perror(current->next->str), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}
