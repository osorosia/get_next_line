/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 09:08:26 by rnishimo          #+#    #+#             */
/*   Updated: 2021/11/16 17:43:43 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	_free_all(char **save, char **buf)
{
	if (save != NULL)
	{
		free(*save);
		*save = NULL;
	}
	if (buf != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
}

static char	*_get_one_line(char **save)
{
	char	*str_before_n;
	char	*str_after_n;

	if (save == NULL)
		return (NULL);
	if (!ft_strchr(*save, '\n'))
	{
		str_after_n = *save;
		*save = NULL;
		return (str_after_n);
	}
	str_before_n = ft_strdup_to_c(*save, '\n');
	str_after_n = ft_strdup_to_c(ft_strchr(*save, '\n') + 1, '\0');
	_free_all(save, NULL);
	if (str_before_n == NULL || str_after_n == NULL)
		return (NULL);
	*save = str_after_n;
	if (*save[0] == '\0')
		_free_all(save, NULL);
	return (str_before_n);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*save = NULL;
	ssize_t		read_byte;

	if (fd < 0 || FD_MAX <= fd || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr(save, '\n'))
		return (_get_one_line(&save));
	read_byte = BUFFER_SIZE;
	buf = NULL;
	while (read_byte == BUFFER_SIZE && !ft_strchr(buf, '\n'))
	{
		save = ft_strjoin_gnl(save, buf);
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (buf == NULL || read_byte < 0)
		{
			_free_all(&save, &buf);
			return (NULL);
		}
		buf[read_byte] = '\0';
	}
	if (read_byte > 0)
		save = ft_strjoin_gnl(save, buf);
	else
		_free_all(NULL, &buf);
	return (_get_one_line(&save));
}
