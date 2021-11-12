/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:18:49 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/11/12 13:30:29 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char			*get_next_line(int fd);
static char		*build_line(int fd, char **acc, char **buffer, size_t b_len);
static char		*nl_in_backup(char **acc);
static char		*nl_in_buffer(char **acc, char **buffer);
static ssize_t	validated_read(int fd, char **acc, char **buffer);

char	*get_next_line(int fd)
{
	static char	*backup = NULL;
	char		*buffer;
	ssize_t		read_val;
	char		*aux;

	aux = nl_in_backup(&backup);
	if (aux)
		return (aux);
	read_val = validated_read(fd, &backup, &buffer);
	if (read_val < 0)
		return (NULL);
	if (read_val == 0)
	{
		aux = NULL;
		if (backup && ft_strlen(backup))
			aux = ft_strndup(backup, ft_strlen(backup));
		if (backup)
			null_free(&backup);
		free(buffer);
		return (aux);
	}
	return (build_line(fd, &backup, &buffer, read_val));
}

static char	*build_line(int fd, char **acc, char **buffer, size_t b_len)
{
	char		*aux;

	aux = nl_in_buffer(acc, buffer);
	if (aux)
		return (aux);
	aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), b_len);
	null_free(acc);
	free(*buffer);
	*acc = ft_strndup(aux, ft_strlen(aux));
	free(aux);
	return (get_next_line(fd));
}

static char	*nl_in_backup(char **acc)
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

static char	*nl_in_buffer(char **acc, char **buffer)
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

static ssize_t	validated_read(int fd, char **acc, char **buffer)
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
