/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frnavarr <frnavarr@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:19:10 by frnavarr          #+#    #+#             */
/*   Updated: 2024/11/01 17:15:20 by frnavarr         ###   ########.fr       */
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

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0)
		return (NULL);
	if (!buffer)
		return (NULL);
	ssize_t	read(int fildes, void *buffer, size_t nbyte);
}
