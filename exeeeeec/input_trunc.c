/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:12:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/08 20:23:48 by cbrice           ###   ########.fr       */
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
		current = current->next;
	}
	return (0);
}
