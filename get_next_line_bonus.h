/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmugnol- <bmugnol-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:18:52 by bmugnol-          #+#    #+#             */
/*   Updated: 2021/11/12 15:01:24 by bmugnol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 256
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*build_line(int fd, char **acc, char **buffer, size_t buffer_len);
char	*nl_in_backup(char **acc);
char	*nl_in_buffer(char **acc, char **buffer);
ssize_t	validated_read(int fd, char **acc, char **buffer);

size_t	ft_strlen(const char *s);
void	null_free(char **p);
char	*ft_strchr(const char *s, int c);
char	*ft_strndup(const char *s, size_t size);
char	*ft_strnjoin(char *s1, char *s2, size_t s1_len, size_t s2_len);

#endif
