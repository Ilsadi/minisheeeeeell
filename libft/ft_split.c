/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:14:00 by ilsadi            #+#    #+#             */
/*   Updated: 2025/04/26 15:14:00 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*malloc_word(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	fill_tab(char **tab, char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] != c)
		{
			tab[i] = malloc_word(s + j, c);
			if (!tab[i])
			{
				tab[i] = NULL;
				return (-1);
			}
			i++;
			while (s[j] && s[j] != c)
				j++;
		}
		else
			j++;
	}
	tab[i] = NULL;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		count;
	int		code_error;

	if (!s)
		return (NULL);
	count = count_word(s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	code_error = fill_tab(tab, s, c);
	if (code_error == -1)
	{
		free_tab(tab);
		return (NULL);
	}
	return (tab);
}
/*#include <stdio.h>
int    main(void)
{
    char const *tab = "sois prete pour les corrections";
    char **result = ft_split(tab, ' ');
    int i = 0;
    while(result[i])
    {
    printf("tab[%d] = \"%s\"\n", i, result[i]);
    i++;
    }
    return(0);
}*/
