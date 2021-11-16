/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 09:08:26 by rnishimo          #+#    #+#             */
/*   Updated: 2021/11/16 22:19:23 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	_free_all(char **save, char **buf)
{
	size_t	i;
	if (save != NULL)
	{
		i = 0;
		while (i < FD_MAX)
		{
			free(save[i]);
			save[i] = NULL;
		}
	}
	if (buf != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
}

static bool	_strjoin_save_buf(char **save, char **buf)
{
	char	*save_new;

	if (*buf == NULL)
		return (true);
	if (*save == NULL)
	{
		*save = *buf;
		*buf = NULL;
		return (true);
	}
	save_new = ft_strjoin_gnl(*save, *buf);
	free(*save);
	free(*buf);
	if (save_new == NULL)
		return (false);
	*save = save_new;
	return (true);
}

static char	*_get_one_line(int fd, char **save)
{
	char	*str_before_n;
	char	*str_after_n;

	if (save == NULL || save[fd] == NULL)
		return (NULL);
	if (!ft_strchr(save[fd], '\n'))
	{
		str_after_n = save[fd];
		save[fd] = NULL;
		return (str_after_n);
	}
	str_before_n = ft_strdup_to_c(save[fd], '\n');
	if (str_before_n == NULL)
	{
		_free_all(save, NULL);
		return (NULL);
	}
	str_after_n = ft_strdup_to_c(ft_strchr(save[fd], '\n') + 1, '\0');
	_free_all(save, NULL);
	if (str_after_n == NULL)
		return (NULL);
	save[fd] = str_after_n;
	if (save[fd][0] == '\0')
		_free_all(save, NULL);
	return (str_before_n);
}

static ssize_t	_read_gnl(int fd, char **save, char **buf)
{
	ssize_t	read_byte;

	if (!_strjoin_save_buf(save, buf))
		return (-1);
	*buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (*buf == NULL)
	{
		_free_all(save, NULL);
		return (-1);
	}
	read_byte = read(fd, *buf, BUFFER_SIZE);
	if (read_byte < 0)
	{
		_free_all(save, buf);
		return (-1);
	}
	(*buf)[read_byte] = '\0';
	return (read_byte);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*save[FD_MAX] = {NULL};
	ssize_t		read_byte;

	if (fd < 0 || FD_MAX <= fd || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr(save[fd], '\n'))
		return (_get_one_line(fd, save));
	read_byte = BUFFER_SIZE;
	buf = NULL;
	while (read_byte == BUFFER_SIZE && !ft_strchr(buf, '\n'))
		read_byte = _read_gnl(fd, save, &buf);
	if (read_byte > 0)
	{
		if (!_strjoin_save_buf(save, &buf))
		{
			_free_all(save, &buf);
			return (NULL);
		}
	}
	if (read_byte == 0)
		free(buf);
	if (read_byte < 0)
		return (NULL);
	return (_get_one_line(fd, save));
}
