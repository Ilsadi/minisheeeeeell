/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:44:26 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/17 15:09:45 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(char *str, char **envp)
{
	if (!pars_double_quotes(str) || !pars_single_quotes(str))
		return (0);
	if (!pars_slash(str))
		return (0);
	if (!pars_pipe(str))
		return (0);
	if (!pars_redir(str))
		return (0);
	str = pars_expand(str, envp);
	return (1);
}
