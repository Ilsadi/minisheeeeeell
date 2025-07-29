/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/29 19:33:22 by ilsadi           ###   ########.fr       */
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
	while (1)
	{
		rl_on_new_line();
		//rl_replace_line("", 0);
		line = readline(">Minisheeeeel : ");
		if (line == NULL)
			break ;
		if (line && *line)
			add_history(line);
		parsing(line, &mini);
		free(line);
		clear_history();
	}
	ft_printf("exit\n");
	return (0);
}
