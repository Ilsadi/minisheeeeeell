/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/24 17:41:22 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_var	**result;

	(void)ac;
	(void)av;

	result = created_tab(envp);
	if (!result)
		return (1);
	// print_tab(result);
	while (1)
	{
		line = readline(" Minisheeeeeeeeell ✗ ");
		if (line == NULL)
		{
			break ;
		}
		if (*line)
			add_history(line);
		parsing(line, envp, result);
		free(line);
	}
	ft_printf("exit\n");
	return (0);
}
