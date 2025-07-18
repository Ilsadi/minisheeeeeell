/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:20:50 by ilsadi            #+#    #+#             */
/*   Updated: 2025/04/26 15:20:50 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t len_dest)
{
	size_t	len_src;
	size_t	i;

	i = 0;
	if (len_dest > 0)
	{
		while (i < len_dest - 1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	len_src = ft_strlen(src);
	return (len_src);
}
