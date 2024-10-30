/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalana- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:45:12 by ebalana-          #+#    #+#             */
/*   Updated: 2024/10/22 17:29:38 by ebalana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*newline(char *box)
{
	int		i;
	char	*line;

	i = 0;
	if (!box[i])
		return (NULL);
	while (box[i] && box[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (box[i] && box[i] != '\n')
	{
		line[i] = box[i];
		i++;
	}
	if (box[i] == '\n')
	{
		line[i] = box[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_box(char *box)
{
	int		i;
	int		j;
	char	*newbox;

	i = 0;
	if (!box)
		return (NULL);
	while (box[i] != '\0' && box[i] != '\n')
		i++;
	if (!box[i])
	{
		free(box);
		box = NULL;
		return (NULL);
	}
	newbox = (char *)malloc((ft_strlen(box) - i + 1) * sizeof(char));
	if (!newbox)
		return (NULL);
	i++;
	j = 0;
	while (box[i])
		newbox[j++] = box[i++];
	newbox[j] = '\0';
	free(box);
	return (newbox);
}

char	*read_file(int fd, char *box)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(box, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(box);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		box = ft_strjoin(box, buffer);
	}
	free(buffer);
	return (box);
}

char	*get_next_line(int fd)
{
	static char	*box[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	box[fd] = read_file(fd, box[fd]);
	if (!box[])
		return (NULL);
	line = newline(box[fd]);
	box[fd] = update_box(box[fd]);
	return (line);
}
