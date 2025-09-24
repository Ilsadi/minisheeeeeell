/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_numeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:18:01 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 17:59:09 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	numeric_sign(const char *str, int *sign)
{
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		return (1);
	}
	*sign = 1;
	return (0);
}

static unsigned long long	numeric_limit(int sign)
{
	if (sign == -1)
		return ((unsigned long long)(-(LLONG_MIN + 1)) + 1);
	return (LLONG_MAX);
}

static int	numeric_check(const char *str, unsigned long long limit)
{
	unsigned long long	result;
	int					i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		result = result * 10 + (str[i] - '0');
		if (result > limit)
			return (0);
		i++;
	}
	return (1);
}

int	is_numeric(char *str)
{
	int					i;
	int					sign;
	unsigned long long	limit;

	i = 0;
	if (!str || !*str)
		return (0);
	i += numeric_sign(str, &sign);
	if (!str[i])
		return (0);
	limit = numeric_limit(sign);
	return (numeric_check(str + i, limit));
}
