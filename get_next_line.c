/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frnavarr <frnavarr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:19:10 by frnavarr          #+#    #+#             */
/*   Updated: 2024/11/04 15:11:41 by frnavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

	//comprobar fd y las asignaciones de memoria
	//llamar ft para leer fd hasta encontrar \n o \0
	//liberar buffer para evitar fugas de memoria
	//fijar linea y retornar la linea con ft
char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;
	ssize_t	bytes_read;
	
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
}

int main(void)
{
	int		fd;
	char	*line;
	
	fd = open("archivo.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return (1);
	}
	while (line = get_next_line(fd) != NULL)
	{
		printf("%s", line);
		free (line);
	}
	close(fd);
	return (0);
}