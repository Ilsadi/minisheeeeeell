/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/17 15:08:42 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	(void)ac;
	(void)av;

	while (1)
	{
		line = readline(" Minisheeeeeeeeell ✗ ");
		if (line == NULL)
		{
			break ;
		}
		if (*line)
			add_history(line);
		if (parsing(line, envp))
			ft_printf("ca maaaarche !\n");
		if (ft_strncmp(line, "exit", 4) == 0)
			break ;
		free(line);
	}
	ft_printf("exit\n");
	return (0);
}
