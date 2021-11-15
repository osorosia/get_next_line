/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 09:09:21 by rnishimo          #+#    #+#             */
/*   Updated: 2021/11/15 22:26:00 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr;

	if (s == NULL)
		return (NULL);
	chr = (char)c;
	while (*s != chr && *s != '\0')
		s++;
	if (*s == chr)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup_to_c(const char *s1, char c)
{
	char	*str;
	size_t	str_len;
	size_t	i;

	str_len = ft_strlen_to_c(s1, c);
	str = (char *)malloc(sizeof(char) * str_len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	while (start > 0 && *s != '\0')
	{
		s++;
		start--;
	}
	s_len = ft_strlen_to_c(s, '\0');
	if (len > s_len)
		len = s_len;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	if (s2 == NULL)
		return (NULL);
	s1_len = ft_strlen_to_c(s1, '\0');
	s2_len = ft_strlen_to_c(s2, '\0');
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == NULL)
	{
		free((char *)s1);
		free((char *)s2);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1 && s1[j] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free((char *)s1);
	free((char *)s2);
	return (str);
}

size_t	ft_strlen_to_c(const char *str, const char c)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}
