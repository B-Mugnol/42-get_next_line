/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:22:36 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/11/03 14:11:38 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*build_line(int fd, char **acc, char **buffer, size_t buffer_len);

// static ssize_t	validated_read(int fd, char **backup, char **buffer)
// {
// 	ssize_t		read_val;

// 	if (*buffer)
// 		free(*buffer);
// 	*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!*buffer)
// 		return (0);
// 	read_val = read(fd, *buffer, BUFFER_SIZE);
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

	if (!*acc) // || !**acc
		return (NULL);
	// acc isn't properly null terminated?
	acc_nl = ft_strchr(*acc, '\n');
	if (acc_nl)
	{
		// write(1, "0: ", 3);
		aux = ft_strndup(acc_nl + 1, ft_strlen(acc_nl + 1));
		result = ft_strndup(*acc, acc_nl - *acc + 1);
		null_free(acc);
		// free(*acc);
		*acc = ft_strndup(aux, ft_strlen(aux));
		null_free(&aux);
		// free(aux);
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
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_val = read(fd, buffer, BUFFER_SIZE);
	if (read_val <= 0 || fd < 0)
	{
		null_free(&buffer);
		// free(buffer);
		// write(1, "@", 1);
		if (backup)
			null_free(&backup);
			// free(backup);
		return (NULL);
	}
	*(buffer + read_val) = '\0';
	return (build_line(fd, &backup, &buffer, read_val));
}

static char	*build_line(int fd, char **acc, char **buffer, size_t buffer_len)
{
	char		*aux;
	char		*nl;
	ssize_t		read_val;

	if (!*acc) // || !**acc
		*acc = ft_strndup("", 0);
	nl = ft_strchr(*buffer, '\n');
	if (nl)
	{
		if (nl == *buffer)
		{
			// write(1, "1: ", 3);
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), 1);
			null_free(acc);
			// free(*acc);
			*acc = ft_strndup(nl + 1, ft_strlen(nl + 1));
		}
		else if (*(nl + 1) != '\0')
		{
			// write(1, "2: ", 3);
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), nl - *buffer + 1);
			null_free(acc);
			// free(*acc);
			*acc = ft_strndup(nl + 1, ft_strlen(nl + 1));
		}
		else if (*(nl + 1) == '\0')
		{
			// write(1, "3: ", 3);
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), buffer_len);
			null_free(acc);
			// free(*acc);
		}
		else
		{
			// write(1, "4: ", 3);
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), nl - *buffer + 1);
			null_free(acc);
			// free(*acc);
		}
		null_free(buffer);
		// free(*buffer);
		// write(1, "out", 3);
		return (aux);
	}
	else
	{
		// write(1, "5: ", 3);
		aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), buffer_len);
		// printf("\\%lu/", ft_strlen(aux));
		null_free(acc);
		// free(*acc);
		null_free(buffer);
		// free(*buffer);
		*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!*buffer)
			return (NULL);
		*acc = ft_strndup(aux, ft_strlen(aux));
		null_free(&aux);
		// free(aux);
		read_val = read(fd, *buffer, BUFFER_SIZE);
		if (read_val < 0 || fd < 0)
		{
			null_free(buffer);
			// free(*buffer);
			null_free(acc);
			// free(*acc);
			return (NULL);
		}
		*(*buffer + read_val) = '\0';
		if (read_val == 0 && *acc) //  && **acc
		{
			null_free(buffer);
			// free(*buffer);
			return (*acc);
		}
		if (read_val == 0)
		{
			null_free(buffer);
			// free(*buffer);
			null_free(acc);
			// free(*acc);
			return (NULL);
		}
		if (read_val < BUFFER_SIZE)
		{
			// *(*buffer + read_val) = '\0';
			aux = ft_strnjoin(*acc, *buffer, ft_strlen(*acc), read_val);
			null_free(buffer);
			// free(*buffer);
			null_free(acc);
			// free(*acc);
			return (aux);
		}
		// write(1, "@", 1);
		return (build_line(fd, acc, buffer, read_val));
	}
}
