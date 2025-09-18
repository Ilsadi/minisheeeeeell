/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/18 20:03:02 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_mini	mini;
	t_pipex	p;

	setup_signals();
	disable_signal_echo();
	mini = (t_mini){0};
	// p = (t_pipex){0};
	// ft_bzero(&mini, sizeof(t_mini));
	mini.rb = malloc(sizeof(t_rb_list));
	mini.rb->head = NULL;
	(void)ac;
	(void)av;
	mini.env = created_tab(envp);
	update_or_add_var(&mini, "_", "/bin/env");
	if (!mini.env)
		return (1);
	while (1)
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
			parsing(line, &mini, &p);
			rb_free_all(mini.rb);
		}
		free(line);
	}
	clear_history();
	free(mini.rb);
	destroy_tab(mini.env);
	return (0);
}
