/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:22:36 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/10/25 17:49:19 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line_break(char **buffer, char **backup);

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
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_val = read(fd, buffer, BUFFER_SIZE);
	*(buffer + BUFFER_SIZE) = '\0';
	if (read_val <= 0 || fd < 0)
	{
		free(buffer);
		free(backup);
		return (NULL);
	}
	while (read_val < BUFFER_SIZE)
		*(buffer + read_val++) = '\0';
	return (get_line_break(&buffer, &backup));
}

static char	*get_line_break(char **buffer, char **backup)
{
	char	*aux;
	char	*aux_backup;
	char	*curr_buffer;
	char	*new_line;

	if (backup && *backup)
		curr_buffer = *backup;
	else
		curr_buffer = *buffer;
	new_line = ft_strchr(curr_buffer, '\n');
	if (new_line)
	{
		aux_backup = ft_strndup(new_line + 1, ft_strlen(new_line + 1));
		if (new_line == curr_buffer)
			aux = ft_strndup(curr_buffer, 1);
		else if (new_line == curr_buffer + ft_strlen(curr_buffer) - 1)
		{
			aux = ft_strndup(curr_buffer, new_line - curr_buffer + 1);
			if (curr_buffer != *backup)
				free(*backup);
			free(curr_buffer);
			*backup = NULL;
			return (aux);
		}
		else
			aux = ft_strndup(curr_buffer, new_line - curr_buffer);
		if (curr_buffer != *backup)
			free(*backup);
		free(curr_buffer);
		*backup = aux_backup;
	}
	else
	{
		aux = ft_strdup_nl(curr_buffer);
		free(curr_buffer);
	}
	return (aux);
}
