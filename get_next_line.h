/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:22:39 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/10/25 17:45:03 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

// typedef struct s_backup
// {
// 	int		fd;
// 	char	*remainder;
// }	t_backup;

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strndup(const char *s, size_t size);
char	*ft_strdup_nl(const char *s);
// char	*get_line_break(char **buffer, char **backup);
void	*ft_memmove(void *dest, const void *src, size_t size);

#endif
