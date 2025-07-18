/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:12:32 by ilsadi            #+#    #+#             */
/*   Updated: 2025/04/26 15:12:32 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*tmp_str;
	size_t			i;

	tmp_str = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (tmp_str[i] == (unsigned char)c)
			return ((void *)(tmp_str + i));
		i++;
	}
	return (0);
}
