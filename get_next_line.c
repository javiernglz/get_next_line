/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frnavarr <frnavarr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:19:10 by frnavarr          #+#    #+#             */
/*   Updated: 2024/11/08 13:11:26 by frnavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// lee desde el fd y llena el buffer
// Lee caracteres BUFFER_SIZE en cada iteración hasta que 
// haya un carácter \n o \0 en el búfer de línea.

//bytes_read = 1 para poder entrar en el while y comenzar la lectura
static char	*read_line(int fd, char *accumulated_buffer, char *read_buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	bytes_read = 1;
	while (bytes_read > 0)
	{
//		ssize_t	 	 read(int fd, void *buffer, size_t nbyte);
//read lee hasta BUFFER_SIZE bytes de fd y los almacena en read_buffer
//devuelve el numero de bytes leidos y lo asigna a bytes_read
		if (bytes_read == -1)
		{
			free(accumulated_buffer);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		read_buffer[bytes_read] = 0;
		if (!accumulated_buffer)
		{
			accumulated_buffer = ft_strdup("");
			tmp = accumulated_buffer;
			accumulated_buffer = ft_strjoin(tmp, read_buffer);
			free(tmp);
			tmp = NULL;
		}
		if (ft_strchr(read_buffer, '\n'))
			break ;
	}
	return (accumulated_buffer);
}

/* //extrae la linea del buffer hasta el caracter de nueva linea
char	*extract_line(char *line_buffer)
{
	int	i;

	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
} */

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	char		*tmp;
	ssize_t		bytes_read;
	static char	*accumulated_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = read_line(fd, accumulated_buffer, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		tmp = line;
		line = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!line)
			break ;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	// Verificamos si se leyó algo y si estamos al final del archivo
	if (bytes_read < 0 || (bytes_read == 0 && line[0] == '\0'))
	{
		free(line);
		return (ft_strdup(""));
	}
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("libro.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
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