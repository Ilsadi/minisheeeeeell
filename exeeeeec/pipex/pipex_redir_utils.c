/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:20:37 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 20:04:42 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_before_pipe(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (is_redir_token(tokens->type))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	has_input_redirection(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == INPUT || tokens->type == HEREDOC)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	has_output_redirection(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == APPEND || tokens->type == TRUNC)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
