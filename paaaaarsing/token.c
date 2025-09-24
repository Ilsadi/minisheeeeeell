/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:32:08 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 20:15:49 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str, int type, t_mini *mini)
{
	t_token	*new_token;

	new_token = rb_malloc(sizeof(t_token), mini->rb);
	if (!new_token)
		return (NULL);
	if (str)
	{
		new_token->str = rb_strdup(str, mini->rb);
		if (!new_token->str)
			return (NULL);
	}
	else
		new_token->str = NULL;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **head, t_token **last, t_token *new_token)
{
	if (!*head)
	{
		*head = new_token;
		*last = new_token;
	}
	else
	{
		(*last)->next = new_token;
		*last = new_token;
	}
}
