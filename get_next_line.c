/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frnavarr <frnavarr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:19:10 by frnavarr          #+#    #+#             */
/*   Updated: 2024/11/09 11:54:18 by frnavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// lee desde el fd y llena el buffer
// Lee caracteres BUFFER_SIZE en cada iteración hasta que 
// haya un carácter \n o \0 en el búfer de línea.

//bytes_read = 1 para poder entrar en el while y comenzar la lectura
//		ssize_t	 	 read(int fd, void *buffer, size_t nbyte);
//read lee hasta BUFFER_SIZE bytes de fd y los almacena en read_buffer
//devuelve el numero de bytes leidos y lo asigna a bytes_read
static char	*read_line(int fd, char *accumulated_buffer, char *read_buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
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

//extrae la linea del buffer hasta el caracter de nueva linea
//ajusta el line_buffer para que solo contenga la línea completa,
// separada del resto del contenido
// usar despues de haber leido y acumulado los datos.
static char	*extract_line(char *accumulated_buffer)
{
	char	*line;
	char	*remaining_buffer;
	size_t	i;
	size_t len;

	i = 0;
	if (!accumulated_buffer || !accumulated_buffer[0])
		return (NULL);
	while (accumulated_buffer[i] && accumulated_buffer[i] != '\n')
		i++;
	/* Si accumulated_buffer[i] es \n, la expresión suma 1 adicional;
	si no lo es, suma 0. Aseguramos tener espacio suficiente en ambos casos. */
	line = malloc((i + 1 + (accumulated_buffer[i] == '\n')) * sizeof(char));
	if (!line)
		return (NULL);
	while (len < i)
	{
		line[len] = accumulated_buffer[len];
		len++;
	}
	remaining_buffer = ft_strdup(accumulated_buffer + i + 1);
	free(accumulated_buffer);
	accumulated_buffer = remaining_buffer;

	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	ssize_t		bytes_read;
	static char	*accumulated_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = extract_line(accumulated_buffer);
	free(buffer);
	if (line)
		return (line);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		accumulated_buffer = ft_strjoin(accumulated_buffer, buffer);
		line = extract_line(accumulated_buffer);
		if (line)
			break ;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	// Verificamos si se leyó algo y si estamos al final del archivo
	if (bytes_read < 0 || (!line && !accumulated_buffer))
		return (NULL);
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