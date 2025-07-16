/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/16 19:29:46 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline(" Minisheeeeeeeeell ✗ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		if (redirection_heredoc(line))
			ft_printf("ca maaaaaarche\n");
		free(line);
	}
	ft_printf("exit\n");
	return (0);
}
