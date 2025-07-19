/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:44:26 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/19 12:26:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(char *str, char **envp)
{
	if (!pars_quotes(str))
		return (0);
	if (!pars_slash(str))
		return (0);
	if (!pars_pipe(str))
		return (0);
	if (!pars_redir(str))
		return (0);
	str = pars_expand(str, envp);
	ft_printf("%s\n", str);
	return (1);
}
