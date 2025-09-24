/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:23:25 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 17:59:09 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_option_error(char *str, t_mini *mini)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("export: usage: export [-fn] "
		"[name[=value] ...] or export -p\n", 2);
	mini->exit_status = 2;
	return (2);
}
