/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:20:41 by ilsadi            #+#    #+#             */
/*   Updated: 2025/04/26 15:20:41 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;

	i = 0;
	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (destsize <= len_dest)
		return (destsize + len_src);
	else
	{
		while (src[i] && (len_dest + i < destsize - 1))
		{
			dest[len_dest + i] = src[i];
			i++;
		}
	}
	if (len_dest < destsize)
		dest[len_dest + i] = '\0';
	return (len_dest + len_src);
}
