/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarkar <samarkar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:09:27 by samarkar          #+#    #+#             */
/*   Updated: 2025/12/12 00:42:10 by samarkar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdlib.h>

static char	*join_stash(char *stash, char *buffer)
{
	char	*tmp;

	if (!stash)
		return (ft_strdup(buffer));
	tmp = stash;
	stash = ft_strjoin(stash, buffer);
	free(tmp);
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	len;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	len = i;
	if (stash[i] == '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*find_line(char *stash, int fd)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free_and_null(stash));
	read_bytes = 1;
	while (read_bytes > 0 && (!stash || !ft_strchr(stash, '\n')))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		stash = join_stash(stash, buffer);
		if (!stash)
			break ;
	}
	free(buffer);
	if (read_bytes < 0 || !stash)
		return (free_and_null(stash));
	return (stash);
}

static char	*new_stash(char *stash)
{
	char	*n_stash;
	size_t	i;
	size_t	j;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free_and_null(stash));
	i++;
	if (!stash[i])
		return (free_and_null(stash));
	n_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!n_stash)
		return (free_and_null(stash));
	j = 0;
	while (stash[i])
		n_stash[j++] = stash[i++];
	n_stash[j] = '\0';
	free(stash);
	return (n_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_SIZE];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_SIZE)
		return (NULL);
	stash[fd] = find_line(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = new_stash(stash[fd]);
	return (line);
}
