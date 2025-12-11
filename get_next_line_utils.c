/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarkar <samarkar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:30:36 by samarkar          #+#    #+#             */
/*   Updated: 2025/12/12 00:25:03 by samarkar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	i;
	size_t	len;

	len = ft_strlen(s1);
	i = 0;
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	while (i < len)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	b;
	char			*t;

	b = (unsigned char)c;
	t = (char *)s;
	while (*t != '\0')
	{
		if (*t == b)
			return (t);
		t++;
	}
	if (*t == b)
		return (t);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	count;
	size_t	i;
	size_t	j;
	char	*new;

	count = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (count + 1));
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

char	*free_and_null(char *s)
{
	if (s)
		free(s);
	return (NULL);
}
