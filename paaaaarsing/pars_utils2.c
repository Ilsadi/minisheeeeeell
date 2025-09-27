/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:05:06 by cbrice            #+#    #+#             */
/*   Updated: 2025/09/27 20:22:37 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_spaces(t_token **head)
{
	t_token	*first;
	t_token	*tmp;

	first = *head;
	if (!head || !*head)
		return ;
	while (first && first->next)
	{
		tmp = first->next;
		if (first->type == TMP_SPACE)
			*head = tmp;
		else if (tmp->type == TMP_SPACE)
			first->next = tmp->next;
		first = first->next;
	}
}

int	str_ends_with_slash(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	return (len > 0 && s[len - 1] == '/');
}

void	remove_empty_token(t_token **head, t_rb_list *rb)
{
	t_token	*first;
	t_token	*tmp;

	first = *head;
	if (!head || !*head)
		return ;
	while (first && first->next)
	{
		tmp = first->next;
		if (first->type == ARG && tmp->type == ARG
			&& !str_ends_with_slash(first->str))
		{
			first->str = rb_strfreejoin(first->str, tmp->str, rb);
			first->next = tmp->next;
			continue ;
		}
		first = first->next;
	}
}

void	get_good_value(t_token **first)
{
	t_token	*value;
	int		i;

	value = *first;
	while (value)
	{
		if (value->type == ARG)
		{
			i = 0;
			while (value->str[i])
			{
				if (value->str[i] < 0)
					value->str[i] *= -1;
				i++;
			}
		}
		value = value->next;
	}
}

int	is_redir_tok(int type)
{
	return (type >= HEREDOC);
}
