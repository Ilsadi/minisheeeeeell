/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   royal_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:50:34 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/02 18:52:50 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*rb_malloc(size_t size, t_rb_list *rb)
{
	t_rb_node	*node;
	void		*ptr;

	if (!rb)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_rb_node));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = rb->head;
	rb->head = node;
	return (ptr);
}

void	rb_free_all(t_rb_list *rb)
{
	t_rb_node	*current;
	t_rb_node	*tmp;

	if (!rb || !rb->head)
		return ;
	current = rb->head;
	while (current)
	{
		tmp = current;
		if (current->ptr != NULL)
		{
			free(current->ptr);
			current->ptr = NULL;
		}
		current = current->next;
		free(tmp);
	}
	rb->head = NULL;
}