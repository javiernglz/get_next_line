/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frnavarr <frnavarr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:19:10 by frnavarr          #+#    #+#             */
/*   Updated: 2024/11/28 11:46:23 by frnavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_line(int fd, char *accumulated_buffer, char *read_buffer)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		read_buffer[bytes_read] = '\0';
		if (!accumulated_buffer)
			accumulated_buffer = ft_strdup("");
		tmp = accumulated_buffer;
		accumulated_buffer = ft_strjoin(accumulated_buffer, read_buffer);
		free(tmp);
		if (ft_strchr(read_buffer, '\n'))
			break ;
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		free(accumulated_buffer);
		return (NULL);
	}
	return (accumulated_buffer);
}

static char	*extract_line(char **accumulated_buffer)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!(*accumulated_buffer) || !(*accumulated_buffer)[0])
		return (NULL);
	i = 0;
	while ((*accumulated_buffer)[i] && (*accumulated_buffer)[i] != '\n')
		i++;
	line = malloc((i + 1 + ((*accumulated_buffer)[i] == '\n')) * sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = (*accumulated_buffer)[j];
		j++;
	}
	if ((*accumulated_buffer)[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static void	update_accumulated_buffer(char **accumulated_buffer, size_t i)
{
	char	*new_accumulated_buffer;

	if ((*accumulated_buffer)[i])
		new_accumulated_buffer = ft_strdup((*accumulated_buffer) + i);
	else
		new_accumulated_buffer = NULL;
	free(*accumulated_buffer);
	*accumulated_buffer = new_accumulated_buffer;
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*accumulated_buffer[FDMAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	accumulated_buffer[fd] = read_line(fd, accumulated_buffer[fd], buffer);
	free(buffer);
	if (!accumulated_buffer[fd])
		return (NULL);
	line = extract_line(&accumulated_buffer[fd]);
	update_accumulated_buffer(&accumulated_buffer[fd], ft_strlen(line));
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("workbook.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening the file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free (line);
	}
	close(fd);
	return (0);
}
 */