/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:22:36 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/10/22 19:39:28 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// read() < BUFFER_SIZE === end of file;

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*aux;
	char		*buffer;
	char		*new_line;

	if (!backup)
	{
		buffer = ft_strndup(backup, ft_strlen(backup));
		free(backup);
		return (buffer);
	}
	buffer = malloc((BUFFER_SIZE) * sizeof(char));
	if (fd == -1 || !buffer)
		return (NULL);
	if (read(fd, buffer, BUFFER_SIZE) <= 0)
	{
		free(buffer);
		free(backup);
		return (NULL);
	}
	new_line = ft_strchr(buffer, '\n');
	if (new_line)
	{
		backup = ft_strndup(new_line + 1, ft_strlen(new_line + 1));
		aux = ft_strndup(buffer, new_line - buffer);
		free(buffer);
		return (aux);
	}
	return (buffer);
}
