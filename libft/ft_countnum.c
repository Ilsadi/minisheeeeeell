/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:17:49 by ilsadi            #+#    #+#             */
/*   Updated: 2025/05/26 16:23:27 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_num(int n)
{
	int		count;
	long	nb;

	nb = n;
	count = 0;
	if (nb <= 0)
		count = 1;
	while (nb)
	{
		nb /= 10;
		count++;
	}
	return (count);
}
