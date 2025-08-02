/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   royal_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:50:34 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/02 18:50:50 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*gc_malloc(size_t size, t_gc_list *gc)
{
	t_gc_node	*node;
	void		*ptr;

	if (!gc)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc_node));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = gc->head;
	gc->head = node;
	return (ptr);
}

void	gc_free_all(t_gc_list *gc)
{
	t_gc_node	*current;
	t_gc_node	*tmp;

	if (!gc || !gc->head)
		return ;
	current = gc->head;
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
	gc->head = NULL;
}