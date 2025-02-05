/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejagom <alejagom@student.42madird.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:52:08 by gafreire          #+#    #+#             */
/*   Updated: 2025/02/05 18:40:47 by alejagom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_newline(int fd, char *line_buffer, char *buffer)
{
	int	size;

	size = 1;
	while (!ft_strchr(line_buffer, '\n') && size > 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size <= 0)
			return (free (buffer), free (line_buffer), line_buffer = NULL);
		buffer[size] = '\0';
		line_buffer = ft_strjoin(line_buffer, buffer);
		if (!line_buffer)
			return (free (buffer), NULL);
	}
	free(buffer);
	return (line_buffer);
}

char	*extract_line(char *line_buffer)
{
	int		len;
	int		i;
	char	*line;

	len = 0;
	i = 0;
	if (line_buffer == NULL)
		return (NULL);
	while (line_buffer[len] != '\n' && line_buffer[len])
		len++;
	if (line_buffer[len] == '\n')
		len++;
	if (len == 0)
		return (NULL);
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = line_buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*extract_remaining(char	*line_buffer)
{
	int		len;
	int		i;
	char	*rest;

	len = 0;
	i = 0;
	if (line_buffer == NULL)
		return (NULL);
	while (line_buffer[len] != '\n' && line_buffer[len])
		len++;
	if (line_buffer[len] == '\n')
		len++;
	rest = malloc((ft_strlen(line_buffer) - len + 1) * sizeof(char));
	if (!rest)
		return (free (line_buffer), NULL);
	while (line_buffer[len + i] != '\0')
	{
		rest[i] = line_buffer[len + i];
		i++;
	}
	free (line_buffer);
	rest[i] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*line_buffer;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(line_buffer);
		return (line_buffer = NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(line_buffer), line_buffer = NULL);
	line_buffer = read_newline(fd, line_buffer, buffer);
	if (line_buffer == NULL)
		return (free(buffer), free(line_buffer), NULL);
	line = extract_line(line_buffer);
	if (!line)
		return (free (line_buffer), line_buffer = NULL);
	line_buffer = extract_remaining(line_buffer);
	if (!line_buffer)
		return (free (line), NULL);
	if (*line_buffer == '\0')
		return (free(line_buffer), line_buffer = NULL, line);
	return (line);
}

int main(void)
{
	int	fd;
	int o;
	char	*line;
	
	o = 0;
	fd = open("prueba.txt", O_RDONLY);
	while (o <= 4)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		o++;
	}
	close(fd);
}
