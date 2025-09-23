/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:03:39 by cbrice            #+#    #+#             */
/*   Updated: 2025/09/23 21:18:57 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_loop_ctx(t_loop_ctx *ctx, t_loop_init init)
{
	ctx->pipex = init.pipex;
	ctx->current = init.tokens;
	ctx->mini = init.mini;
	ctx->tab_pid = init.tab_pid;
	ctx->envp = var_to_envp(init.mini->env);
	ctx->i = 0;
	ctx->nb_pipes = has_pipe(init.mini->first);
}

static void	setup_and_fork(t_pipex *pipex, t_token **current, t_loop_ctx *ctx)
{
	if (ctx->i < ctx->nb_pipes)
	{
		if (pipe(pipex->pipefd) == -1)
			ft_error_exit("pipe error");
		pipex->fd_out = pipex->pipefd[1];
	}
	else
		pipex->fd_out = pipex->outfile;
	ctx->pipex->pid1 = fork();
	if (ctx->pipex->pid1 == 0)
		ft_child_pro(ctx->pipex, *current, ctx->envp, ctx->mini);
	ctx->tab_pid[ctx->i] = ctx->pipex->pid1;
	while (*current && (*current)->type != PIPE)
		*current = (*current)->next;
	if (*current)
		*current = (*current)->next;
}

void	ft_pipex_loop(t_pipex *pipex, t_token *tokens,
					t_mini *mini, pid_t *tab_pid)
{
	t_loop_ctx	ctx;
	t_loop_init	init;

	init.pipex = pipex;
	init.tokens = tokens;
	init.mini = mini;
	init.tab_pid = tab_pid;
	init_loop_ctx(&ctx, init);
	if (!ctx.envp)
		ft_error_exit("Error: var_to_envp");
	pipex->fd_in = pipex->infile;
	while (ctx.current)
	{
		setup_and_fork(pipex, &ctx.current, &ctx);
		close_test(pipex->fd_in);
		close_test(pipex->fd_out);
		if (ctx.current)
			pipex->fd_in = pipex->pipefd[0];
		ctx.i++;
	}
	ft_free_tab(ctx.envp);
}
