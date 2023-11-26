/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:47:38 by nachab            #+#    #+#             */
/*   Updated: 2022/11/07 13:21:52 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_container(char *buffer)
{
	char	*remain;
	int		i;
	int		j;

	if (!buffer)
		return (0);
	i = newline_index(buffer);
	if (i == 0 || buffer[i] == '\0')
	{
		free(buffer);
		return (0);
	}
	j = 0;
	remain = malloc((ft_strlen(buffer) - i) + 1);
	while (buffer[i])
		remain[j++] = buffer[i++];
	remain[j] = '\0';
	free(buffer);
	return (remain);
}

char	*get_newline(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	if (!buffer)
		return (0);
	i = newline_index(buffer);
	if (newline_index(buffer) == 0)
	{
		line = ft_strdup(buffer);
		return (line);
	}
	j = 0;
	line = malloc(i + 1);
	while (buffer[j])
	{
		line[j] = buffer[j];
		if (buffer[j] == '\n')
			break ;
		j++;
	}
	line[j + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*lread;
	char		*line;
	int			nread;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (0);
	lread = malloc(BUFFER_SIZE + 1);
	if (!lread)
		return (0);
	nread = read(fd, lread, BUFFER_SIZE);
	while (nread > 0)
	{
		lread[nread] = '\0';
		buffer = ft_strjoin(buffer, lread);
		if (newline_index(buffer) > 0)
			break ;
		nread = read(fd, lread, BUFFER_SIZE);
	}
	free(lread);
	line = get_newline(buffer);
	buffer = trim_container(buffer);
	return (line);
}
