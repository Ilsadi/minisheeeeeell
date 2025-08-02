/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/01 13:23:44 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	(void)ac;
	(void)av;

	mini.env = created_tab(envp);
	if (!mini.env)
		return (1);
	// print_tab(result);
	while (!mini.should_exit)
	{
		line = readline(">Minisheeeeel : ");
		if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
		if (line && *line)
		{
			add_history(line);
			parsing(line, &mini);
		}
		free(line);
	}
	destroy_tab(mini.env);
	clear_history();
	return (mini.exit_code);
}
