/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:14 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 22:19:25 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_nonempty_line(char *line, t_mini *mini, t_pipex *p)
{
	add_history(line);
	parsing(line, mini, p);
	rb_free_all(mini->rb);
}

static int	shell_iteration(t_mini *mini, t_pipex *p)
{
	char	*line;

	g_state = STATE_IDLE;
	line = readline(">Minisheeeeel : ");
	if (g_state == STATE_SIGINT)
	{
		mini->exit_status = 130;
        g_state = STATE_IDLE;
        if (line)
            free(line);
        return 0;
	}
	if (!line)
	{
		ft_printf("exit\n");
		return (1);
	}
	if (*line)
		process_nonempty_line(line, mini, p);
	free(line);
	return (0);
}

static void	shell_loop(t_mini *mini, t_pipex *p)
{
	while (1)
		if (shell_iteration(mini, p))
			break ;
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;
	t_pipex	p;

	setup_signals();
	disable_signal_echo();
	ft_bzero(&mini, sizeof(t_mini));
	mini.rb = malloc(sizeof(t_rb_list));
	if (!mini.rb)
		return (1);
	mini.rb->head = NULL;
	(void)ac;
	(void)av;
	mini.env = created_tab(envp);
	update_or_add_var(&mini, "_", "/bin/env");
	if (!mini.env)
	{
		free(mini.rb);
		return (1);
	}
	shell_loop(&mini, &p);
	clear_history();
	free(mini.rb);
	destroy_tab(mini.env);
	return (0);
}
