/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:22:36 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/10/28 12:29:03 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*build_line(int fd, char **acc, char **buffer, size_t buffer_len);

// static ssize_t	validated_read(int fd, char **backup, char **buffer)
// {
// 	ssize_t		read_val;

// 	if (*buffer)
// 		free(buffer);
// 	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buffer)
// 		return (0);
// 	read_val = read(fd, buffer, BUFFER_SIZE);
// 	*(*buffer + BUFFER_SIZE) = '\0';
// 	if (read_val < 0 || fd < 0)
// 	{
// 		free(*buffer);
// 		free(*backup);
// 		return (-1);
// 	}
// 	if (read_val < BUFFER_SIZE)
// 		*(*buffer + read_val) = '\0';
// 	return (read_val);
// }

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buffer;
	ssize_t		read_val;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_val = read(fd, buffer, BUFFER_SIZE);
	// *(buffer + BUFFER_SIZE) = '\0';
	if (read_val <= 0 || fd < 0)
	{
		free(buffer);
		if (*backup)
			free(backup);
		return (NULL);
	}
	// if (read_val < BUFFER_SIZE)
	// {
	// 	return (build_line(fd, &backup, &buffer, read_val));
	// }
	*(buffer + read_val) = '\0';
	return (build_line(fd, &backup, &buffer, read_val));
}

static char	*build_line(int fd, char **acc, char **buffer, size_t buffer_len)
{
	char		*aux;
	char		*nl;
	char		*acc_nl;
	ssize_t		read_val;

	if (!*acc)
		*acc = ft_strndup("", 0);
	nl = ft_strchr(*buffer, '\n');
	if (nl)
	{
		if (nl == *buffer)
		{
			write(1, "1: ", 3);
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), 1);
			free(*acc);
			*acc = ft_strndup(nl + 1, ft_strlen(nl + 1));
		}
		else if (nl != *buffer + buffer_len - 1)
		{
			write(1, "2: ", 3);
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), nl - *buffer + 1);
			free(*acc);
			*acc = ft_strndup(nl + 1, ft_strlen(nl + 1));
		}
		else if (nl == *buffer + buffer_len - 1)
		{
			write(1, "3: ", 3);
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), buffer_len);
			free(*acc);
		}
		else
		{
			write(1, "4: ", 3);
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), nl - *buffer + 1);
			free(*acc);
		}
		free(*buffer);
		acc_nl = ft_strchr(*acc, '\n');
		// if (acc_nl == *acc && acc_nl != NULL && *acc)
		// 	write(1, "@@@@@", 5);
		// if (acc && *acc && **acc)
		// {
		// 	write(1, "@@@@@", 5);
		// 	write(1, "!acc =", 6);
		// 	write(1, *acc, ft_strlen(*acc) + 1);
		// 	write(1, "= acc!", 6);
		// }
		return (aux);
	}
	else
	{
		// write(1, "5: ", 3);
		aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), buffer_len);
		free(*acc);
		free(*buffer);
		*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!*buffer)
			return (NULL);
		*(*buffer + BUFFER_SIZE) = '\0';
		*acc = ft_strndup(aux, ft_strlen(aux));
		free(aux);
		read_val = read(fd, *buffer, BUFFER_SIZE);
		if (read_val < 0 || fd < 0)
		{
			free(*buffer);
			free(*acc);
			return (NULL);
		}
		if (read_val == 0 && **acc)
			return (*acc);
		if (read_val == 0)
		{
			free(*acc);
			return (NULL);
		}
		if (read_val < BUFFER_SIZE)
		{
			*(*buffer + read_val) = '\0';
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), read_val);
			free(*buffer);
			free(*acc);
			return (aux);
		}
		return (build_line(fd, acc, buffer, read_val));
	}
}
