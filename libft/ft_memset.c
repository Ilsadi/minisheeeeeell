/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:32:53 by ilsadi            #+#    #+#             */
/*   Updated: 2025/04/26 13:01:10 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buffer, int c, size_t len)
{
	unsigned char	*tmp_buffer;
	size_t			i;

	i = 0;
	tmp_buffer = (unsigned char *) buffer;
	while (i < len)
	{
		tmp_buffer[i] = (unsigned char) c;
		i++;
	}
	return (buffer);
}
