/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:55:05 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/07 17:09:47 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rb_substr(char const *str, unsigned int st, size_t len, t_rb_list *rb)
{
	size_t	i;
	char	*tab;

	i = 0;
	if (st >= ft_strlen(str))
	{
		tab = rb_malloc(sizeof(char) * 1, rb);
		if (!tab)
			return (NULL);
		tab[0] = '\0';
		return (tab);
	}
	if (ft_strlen(str + st) < len)
		len = ft_strlen(str + st);
	tab = rb_malloc(sizeof(char) * (len + 1), rb);
	if (!tab)
		return (NULL);
	while (i < len)
	{
		tab[i] = str[st + i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*rb_strfreejoin(char *s1, char *s2, t_rb_list *rb)
{
	int		i;
	int		j;
	char	*s3;

	if (!s1)
	{
		s1 = rb_malloc(sizeof(char) * 1, rb);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	s3 = rb_malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char), rb);
	if (!s3)
		return (NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

char	*rb_strdup(const char *src, t_rb_list *rb)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = rb_malloc(sizeof(char) * ft_strlen(src) + 1, rb);
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*rb_calloc(size_t count, size_t size, t_rb_list *rb)
{
	void	*buffer;

	if (count != 0 && size > (size_t) - 1 / count)
		return (NULL);
	if (count == 0 || size == 0)
		buffer = rb_malloc(0, rb);
	else
		buffer = rb_malloc(count * size, rb);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, count * size);
	return (buffer);
}
