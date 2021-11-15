/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 09:08:26 by rnishimo          #+#    #+#             */
/*   Updated: 2021/11/15 21:11:45 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define FD_MAX 256

// main
char	*get_next_line(int fd);

// utils
char	*ft_strchr(const char *s, int c);
char	*ft_strdup_to_c(const char *s1, char c);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen_to_c(const char *str, char c);

#endif
