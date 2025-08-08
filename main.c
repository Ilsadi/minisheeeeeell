/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/08 17:10:43 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_mini mini;

	setup_signals();
	disable_signal_echo();
	
	ft_bzero(&mini, sizeof(t_mini));
	mini.rb = malloc(sizeof(t_rb_list));
	mini.rb->head = NULL;
	(void)ac;
	(void)av;

	mini.env = created_tab(envp, &mini);
	if (!mini.env)
		return (1);
	// print_tab(result);
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
			parsing(line, &mini);
			rb_free_all(mini.rb);
		}
		free(line);
	}
	clear_history();
	free(mini.rb);
	destroy_tab(mini.env);
	printf("DEBUG: env destroyed\n");
	return (0);
}
