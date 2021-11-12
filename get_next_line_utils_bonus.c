/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:18:55 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/11/12 13:30:34 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	null_free(char **p)
{
	free(*p);
	*p = NULL;
}

size_t	ft_strlen(const char *s)
{
	const char	*p;

	if (!s)
		return (0);
	p = s;
	while (*p != '\0')
		p++;
	return ((size_t)(p - s));
}

char	*ft_strchr(const char *s, int c)
{
	char	cast_c;

	if (!s)
		return (NULL);
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

char	*ft_strnjoin(char *s1, char *s2, size_t s1_len, size_t s2_len)
{
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc((s1_len + s2_len + 1) * sizeof (char));
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (*s1 != '\0' && i < s1_len)
		*(s3 + i++) = *s1++;
	while (*s2 != '\0' && j++ < s2_len)
		*(s3 + i++) = *s2++;
	*(s3 + i) = '\0';
	return (s3);
}

char	*ft_strndup(const char *s, size_t size)
{
	char	*dest;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = 0;
	while (*(s + len) != '\0' && len < size)
		len++;
	dest = malloc((len + 1) * sizeof (char));
	if (!dest)
		return (NULL);
	i = 0;
	while (*(s + i) != '\0' && i < size)
	{
		*(dest + i) = *(s + i);
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}
