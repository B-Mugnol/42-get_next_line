/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:22:33 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/10/25 14:04:26 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p != '\0')
		p++;
	return ((size_t)(p - s));
}

char	*ft_strchr(const char *s, int c)
{
	char	cast_c;

	cast_c = (char)(c);
	while (*s != '\0')
	{
		if (*s == cast_c)
			return ((char *)(s));
		s++;
	}
	if (cast_c == '\0')
		return ((char *)(s));
	return (NULL);
}

char	*ft_strndup(const char *s, size_t size)
{
	char	*dest;
	size_t	len;

	len = 0;
	while (*(s + len) != '\0' && len < size)
		len++;
	dest = malloc((len + 1) * sizeof (char));
	if (!dest)
		return (NULL);
	dest = ft_memmove(dest, s, len + 1);
	*(dest + len + 1) = '\0';
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char	*cast_src;
	char	*cast_dest;
	size_t	i;

	cast_src = (char *)(src);
	cast_dest = (char *)(dest);
	i = 0;
	if (src > dest)
	{
		while (i < size)
		{
			*(cast_dest + i) = *(cast_src + i);
			i++;
		}
	}
	else if (dest > src)
	{
		while (i < size)
		{
			*(cast_dest + size - i - 1) = *(cast_src + size - i - 1);
			i++;
		}
	}
	return (dest);
}

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
