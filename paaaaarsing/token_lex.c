/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:20:05 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 20:15:49 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	return (c == ' ');
}

static int	is_op(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	add_tmp_space_if_needed(char *line, int i, t_mini *mini,
		t_tokctx *ctx)
{
	t_token	*sp;

	if (!line[i] || !is_space(line[i]))
		return (0);
	sp = create_token(NULL, TMP_SPACE, mini);
	if (!sp)
		return (-1);
	add_token(ctx->head, ctx->cur, sp);
	return (0);
}

static int	handle_quote_after_op(char *line, int *i, t_mini *mini,
		t_tokctx *ctx)
{
	t_token	*tok;

	tok = quotes(line, i, mini);
	if (!tok)
		return (-1);
	add_token(ctx->head, ctx->cur, tok);
	return (0);
}

static int	add_arg_after_op(char *line, int *i, t_mini *mini,
		t_tokctx *ctx)
{
	int		start;
	char	*word;
	t_token	*arg_tok;

	start = *i;
	while (line[*i] && !is_space(line[*i]) && !is_op(line[*i]))
		(*i)++;
	if (*i <= start)
		return (0);
	word = rb_substr(line, start, *i - start, mini->rb);
	if (!word)
		return (-1);
	arg_tok = create_token(word, ARG, mini);
	if (!arg_tok)
		return (-1);
	add_token(ctx->head, ctx->cur, arg_tok);
	return (0);
}

static int	handle_operator_branch(char *line, int *i, t_mini *mini,
		t_tokctx *ctx)
{
	t_token	*tok;

	tok = operator(line, i, mini);
	if (!tok)
		return (-1);
	add_token(ctx->head, ctx->cur, tok);
	if (is_quote(line[*i]))
		return (handle_quote_after_op(line, i, mini, ctx));
	return (add_arg_after_op(line, i, mini, ctx));
}

static int	handle_word_branch(char *line, int *i, t_mini *mini,
		t_tokctx *ctx)
{
	int		start;
	char	*word;
	t_token	*tok;

	start = *i;
	while (line[*i] && !is_space(line[*i]) && !is_op(line[*i])
		&& !is_quote(line[*i]))
		(*i)++;
	word = rb_substr(line, start, *i - start, mini->rb);
	if (!word)
		return (-1);
	tok = create_token(word, ARG, mini);
	if (!tok)
		return (-1);
	add_token(ctx->head, ctx->cur, tok);
	return (0);
}

static int	process_next_token(char *line, int *i, t_mini *mini,
		t_tokctx *ctx)
{
	t_token	*tok;

	while (is_space(line[*i]))
		(*i)++;
	if (!line[*i])
		return (1);
	if (is_quote(line[*i]))
	{
		tok = quotes(line, i, mini);
		if (!tok)
			return (-1);
		add_token(ctx->head, ctx->cur, tok);
	}
	else if (is_op(line[*i]))
	{
		if (handle_operator_branch(line, i, mini, ctx) < 0)
			return (-1);
	}
	else if (handle_word_branch(line, i, mini, ctx) < 0)
		return (-1);
	if (add_tmp_space_if_needed(line, *i, mini, ctx) < 0)
		return (-1);
	return (0);
}

 t_token	*tokenize(char *line, t_mini *mini)
{
	t_token		*head;
	t_token		*current;
	t_tokctx	ctx;
	int			i;
	int			ret;

	head = NULL;
	current = NULL;
	ctx.head = &head;
	ctx.cur = &current;
	i = 0;
	while (line[i])
	{
		ret = process_next_token(line, &i, mini, &ctx);
		if (ret != 0)
		{
			if (ret < 0)
				return (NULL);
			return (head);
		}
	}
	return (head);
}
