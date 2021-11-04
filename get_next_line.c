/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:22:36 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/11/04 16:48:52 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*build_line(int fd, char **acc, char **buffer, size_t buffer_len);
static void	null_free(char **p);

static ssize_t	validated_read(int fd, char **acc, char **buffer)
{
	ssize_t		read_val;

	*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!*buffer)
		return (-1);
	read_val = read(fd, *buffer, BUFFER_SIZE);
	if (read_val < 0 || fd < 0)
	{
		free(*buffer);
		if (*acc)
			null_free(acc);
		return (-1);
	}
	*(*buffer + read_val) = '\0';
	return (read_val);
}

static void	null_free(char **p)
{
	free(*p);
	*p = NULL;
}

static char	*do_thing(char **acc)
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

char	*get_next_line(int fd)
{
	static char	*backup = NULL;
	char		*buffer;
	ssize_t		read_val;
	char		*aux;

	aux = do_thing(&backup);
	if (aux)
		return (aux);
	read_val = validated_read(fd, &backup, &buffer);
	////
	// if (read_val == 0 && backup)
	// {
	// 	free(buffer);
	// 	if (ft_strlen(backup))
	// 		aux = ft_strndup(backup, ft_strlen(backup));
	// 	else
	// 		aux = NULL;
	// 	null_free(&backup);
	// 	return (aux);
	// }
	// if (read_val <= 0)
	// 	return (NULL);
	////
	if (read_val < 0)
		return (NULL);
	if (read_val == 0)
	{
		if (backup && ft_strlen(backup))
		{
			free(buffer);
			aux = ft_strndup(backup, ft_strlen(backup));
			null_free(&backup);
			return (aux);
		}
		free(buffer);
		if (backup)
			null_free(&backup);
		return (NULL);
	}
	return (build_line(fd, &backup, &buffer, read_val));
}

static char	*build_line(int fd, char **acc, char **buffer, size_t buffer_len)
{
	char		*aux;
	char		*nl;
	ssize_t		read_val;

	if (!*acc)
		*acc = ft_strndup("", 0);
	nl = ft_strchr(*buffer, '\n');
	if (nl)
	{
		if (nl == *buffer)
		{
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), 1);
			free(*acc);
			*acc = ft_strndup(nl + 1, ft_strlen(nl + 1));
		}
		else if (*(nl + 1) != '\0')
		{
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), nl - *buffer + 1);
			free(*acc);
			*acc = ft_strndup(nl + 1, ft_strlen(nl + 1));
		}
		else if (*(nl + 1) == '\0')
		{
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), buffer_len);
			null_free(acc);
		}
		else
		{
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), nl - *buffer + 1);
			null_free(acc);
		}
		free(*buffer);
		return (aux);
	}
	else
	{
		aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), buffer_len);
		null_free(acc);
		free(*buffer);
		*acc = ft_strndup(aux, ft_strlen(aux));
		free(aux);
		read_val = validated_read(fd, acc, buffer);
		if (read_val < 0)
			return (NULL);
		if (read_val == 0 && *acc)
		{
			free(*buffer);
			aux = ft_strndup(*acc, ft_strlen(*acc));
			null_free(acc);
			return (aux);
		}
		if (read_val == 0)
		{
			free(*buffer);
			null_free(acc);
			return (NULL);
		}

		if (read_val < BUFFER_SIZE)
		{
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), read_val);
			free(*buffer);
			null_free(acc);
			return (aux);
		}
		return (build_line(fd, acc, buffer, read_val));
	}
}
