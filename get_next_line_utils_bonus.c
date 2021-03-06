/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 09:09:21 by rnishimo          #+#    #+#             */
/*   Updated: 2021/11/30 11:43:48 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	str = (char *)malloc(sizeof(char) * str_len + 2);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	s1_len = ft_strlen_to_c(s1, '\0');
	s2_len = ft_strlen_to_c(s2, '\0');
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < s1_len)
		str[i++] = s1[j++];
	j = 0;
	while (j < s2_len)
		str[i++] = s2[j++];
	str[i] = '\0';
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
