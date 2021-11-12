/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:18:49 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/11/12 15:01:28 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*backup[MAX_FD];
	char		*buffer;
	ssize_t		read_val;
	char		*aux;

	if (fd < 0 || fd > MAX_FD)
		return (NULL);
	aux = nl_in_backup(backup + fd);
	if (aux)
		return (aux);
	read_val = validated_read(fd, backup + fd, &buffer);
	if (read_val < 0)
		return (NULL);
	if (read_val == 0)
	{
		aux = NULL;
		if (backup + fd && ft_strlen(*(backup + fd)))
			aux = ft_strndup(*(backup + fd), ft_strlen(*(backup + fd)));
		if (backup + fd)
			null_free(backup + fd);
		free(buffer);
		return (aux);
	}
	return (build_line(fd, backup + fd, &buffer, read_val));
}

char	*build_line(int fd, char **acc, char **buffer, size_t buffer_len)
{
	char		*aux;

	aux = nl_in_buffer(acc, buffer);
	if (aux)
		return (aux);
	aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), buffer_len);
	null_free(acc);
	free(*buffer);
	*acc = ft_strndup(aux, ft_strlen(aux));
	free(aux);
	return (get_next_line(fd));
}

char	*nl_in_backup(char **acc)
{
	char	*acc_nl;
	char	*result;
	char	*aux;

	if (!*acc || !**acc)
		return (NULL);
	acc_nl = ft_strchr(*acc, '\n');
	if (acc_nl)
	{
		aux = ft_strndup(acc_nl + 1, ft_strlen(acc_nl + 1));
		result = ft_strndup(*acc, acc_nl - *acc + 1);
		free(*acc);
		*acc = ft_strndup(aux, ft_strlen(aux));
		free(aux);
		return (result);
	}
	return (NULL);
}

char	*nl_in_buffer(char **acc, char **buffer)
{
	char		*aux;
	char		*nl;

	if (!*acc)
		*acc = ft_strndup("", 0);
	nl = ft_strchr(*buffer, '\n');
	if (!nl)
		return (NULL);
	aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), nl - *buffer + 1);
	if (nl == *buffer || *(nl + 1) != '\0')
	{
		free(*acc);
		*acc = ft_strndup(nl + 1, ft_strlen(nl + 1));
	}
	else
		null_free(acc);
	free(*buffer);
	return (aux);
}

ssize_t	validated_read(int fd, char **acc, char **buffer)
{
	ssize_t		read_val;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > MAX_FD)
		return (-1);
	*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!*buffer)
		return (-1);
	read_val = read(fd, *buffer, BUFFER_SIZE);
	if (read_val < 0)
	{
		free(*buffer);
		if (*acc)
			null_free(acc);
		return (-1);
	}
	*(*buffer + read_val) = '\0';
	return (read_val);
}
