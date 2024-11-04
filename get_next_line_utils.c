/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frnavarr <frnavarr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:03:39 by frnavarr          #+#    #+#             */
/*   Updated: 2024/11/04 15:13:42 by frnavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(s);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
		return (0);
	ft_strlcpy(copy, s, len + 1);
	return (copy);
}

// lee desde el fd y llena el buffer
// Lee caracteres BUFFER_SIZE en cada iteración hasta que 
// haya un carácter \n o \0 en el búfer de línea.

//bytes_read = 1 para poder entrar en el while y comenzar la lectura
static char	*read_line(int fd, char *read_buffer, char *accumulated_buffer)
{
	ssize_t	bytes_read;
	
	bytes_read = 1;
	while (bytes_read > 0)
	{
//		ssize_t	 	 read(int fildes, void *buffer, size_t nbyte);
//read lee hasta BUFFER_SIZE bytes de fd y los almacena en read_buffer
//devuelve el numero de bytes leidos y lo asigna a bytes_read
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		else if (bytes_read == 0)
			break;
	}
}

//extrae la linea del buffer hasta el caracter de nueva linea
char	*extract_line(char *line_buffer)
{
	int	i;
	
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
}

//borrar el contenido restante del buffer dsp de extraer
//clean_buffer

//libera la memoria asignada para evitar fugas
//mem_free 

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	join = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcpy(join + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (join);
}

