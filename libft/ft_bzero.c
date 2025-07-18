/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:46:58 by ilsadi            #+#    #+#             */
/*   Updated: 2025/05/05 10:46:16 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*tmp_str;
	size_t			i;

	i = 0;
	tmp_str = (unsigned char *) str;
	while (i < n)
	{
		tmp_str[i] = 0;
		i++;
	}
}
