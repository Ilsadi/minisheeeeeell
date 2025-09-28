/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lex_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:43:06 by cbrice            #+#    #+#             */
/*   Updated: 2025/09/28 15:44:33 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ');
}

int	is_op(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	add_tmp_space_if_needed(char *line, int i, t_mini *mini,
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

int	handle_quote_after_op(char *line, int *i, t_mini *mini,
		t_tokctx *ctx)
{
	t_token	*tok;

	tok = quotes(line, i, mini);
	if (!tok)
		return (-1);
	add_token(ctx->head, ctx->cur, tok);
	return (0);
}
