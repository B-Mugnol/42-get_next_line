/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:22:36 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/10/24 14:53:40 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*backup;
	ssize_t		read_val;
	char		*aux;
	char		*buffer;
	char		*new_line;

	if (backup)
	{
		buffer = ft_strndup(backup, ft_strlen(backup));
		free(backup);
		backup = NULL;
		// aux_f
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
	buffer = malloc((BUFFER_SIZE) * sizeof(char));
	read_val = read(fd, buffer, BUFFER_SIZE);
	if (read_val <= 0 || fd == -1 || !buffer)
	{
		free(buffer);
		free(backup);
		return (NULL);
	}
	else if (read_val < BUFFER_SIZE)
		*(buffer + read_val) = '\0';
	// aux_f
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
