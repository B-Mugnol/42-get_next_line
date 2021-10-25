/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:22:36 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/10/25 14:03:55 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line_break(char **buffer, char **backup)
{
	char	*new_line;
	char	*aux;

	new_line = ft_strchr(*buffer, '\n');
	if (new_line)
	{
		*backup = ft_strndup(new_line + 1, ft_strlen(new_line + 1));
		aux = ft_strndup(*buffer, new_line - *buffer);
		free(*buffer);
		return (aux);
	}
	return (*buffer);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buffer;
	ssize_t		read_val;

	if (backup && *backup)
	{
		buffer = ft_strndup(backup, ft_strlen(backup));
		free(backup);
		backup = NULL;
		return (get_line_break(&buffer, &backup));
	}
	buffer = malloc((BUFFER_SIZE) * sizeof(char));
	read_val = read(fd, buffer, BUFFER_SIZE);
	if (read_val <= 0 || fd < 0 || !buffer)
	{
		free(buffer);
		free(backup);
		return (NULL);
	}
	else if (read_val < BUFFER_SIZE)
		*(buffer + read_val) = '\0';
	return (get_line_break(&buffer, &backup));
}
