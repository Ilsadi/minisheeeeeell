/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:52:04 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/18 19:13:54 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pars_expand(char *str, char **envp)
{
	int		i;
	int		j;
	char	*varname;
	int		start;
	char	*vareplace;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			start = i;
			while (ft_isalpha(str[i]) || str[i] == '_')
			{
				i++;
			}
			varname = malloc(sizeof(char) * (i - start + 1));
			ft_substr(str, start, i);
		}
		i++;
	}
	while (envp[j])
	{
		if (strcmp(envp[j], varname) == 0)
		{
			vareplace = envp[j] + ft_strlen(varname + 1);
		}
	}
}
