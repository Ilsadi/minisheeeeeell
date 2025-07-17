/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:52:04 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/17 15:10:27 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pars_expand(char *str, char **envp)
{
	int		i;
	int		j;
	int		len;
	char	*varname;
	char	*value;
	int		start;
	int		k;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = 0;
			len = 0;
			i++;
			start = i;
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			if (i > 0)
			{
				varname = malloc(sizeof(char) * (i + 1));
				if (!varname)
					return (0);
				ft_strlcpy(varname, &str[start], i + 1);
				while (envp[j])
				{
					k = 0;
					while (envp[j][k] && envp[j][k] != '=')
						k++;
					if ((int)ft_strlen(varname) == k && ft_strncmp(envp[j], varname, k) == 0)
					{
						value = envp[j] + k + 1;
						break ;
					}
					j++;
				}
				free(varname);
			}

		}
		else
			i++;
	}
	return (value);
}
