/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 09:08:26 by rnishimo          #+#    #+#             */
/*   Updated: 2021/11/30 11:23:31 by rnishimo         ###   ########.fr       */
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

static bool	_strjoin_and_free(char **save, char **buf)
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
	save_new = ft_strjoin(*save, *buf);
	_free_all(save, buf);
	if (save_new == NULL)
		return (false);
	*save = save_new;
	return (true);
}

static char	*_get_one_line(char **save)
{
	char	*str_before_n;
	char	*str_after_n;

	if (save == NULL || *save == NULL)
		return (NULL);
	if (!ft_strchr(*save, '\n'))
	{
		str_after_n = *save;
		*save = NULL;
		return (str_after_n);
	}
	str_before_n = ft_strdup_to_c(*save, '\n');
	if (str_before_n == NULL)
	{
		_free_all(save, NULL);
		return (NULL);
	}
	str_after_n = ft_strdup_to_c(ft_strchr(*save, '\n') + 1, '\0');
	_free_all(save, NULL);
	if (str_after_n == NULL)
		return (NULL);
	*save = str_after_n;
	if (*save[0] == '\0')
		_free_all(save, NULL);
	return (str_before_n);
}

static ssize_t	_read_gnl(int fd, char **save, char **buf)
{
	ssize_t	read_byte;

	if (!_strjoin_and_free(save, buf))
		return (-1);
	*buf = (char *)malloc(sizeof(char) * ((ssize_t)BUFFER_SIZE + 1));
	if (*buf == NULL)
		return (-1);
	read_byte = read(fd, *buf, BUFFER_SIZE);
	if (read_byte < 0)
		return (-1);
	(*buf)[read_byte] = '\0';
	return (read_byte);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*buf;
	ssize_t		read_byte;

	if (fd < 0 || FD_MAX <= fd
		|| (ssize_t)BUFFER_SIZE <= 0 || SSIZE_MAX < (ssize_t)BUFFER_SIZE)
		return (NULL);
	if (ft_strchr(save, '\n'))
		return (_get_one_line(&save));
	read_byte = (ssize_t)BUFFER_SIZE;
	buf = NULL;
	while (read_byte == BUFFER_SIZE && !ft_strchr(buf, '\n'))
		read_byte = _read_gnl(fd, &save, &buf);
	if (read_byte > 0)
	{
		if (!_strjoin_and_free(&save, &buf))
			return (NULL);
	}
	if (read_byte == 0)
		_free_all(NULL, &buf);
	if (read_byte < 0)
		_free_all(&save, &buf);
	return (_get_one_line(&save));
}
