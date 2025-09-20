/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:27:45 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/20 17:17:13 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *msg)
{
	ft_putstr_fd(msg, 2);
}

void	command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	is_a_directory(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}
