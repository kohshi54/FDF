/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 03:14:04 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/19 20:26:41 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strchr_gnl(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		if (s[i++] == (char)c)
			return (i);
	if (s[i] == (char)c)
		return (i);
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char	*p;
	char	*head;
	char	*s_head;

	p = malloc(ft_strchr_gnl(s1, '\0') + ft_strchr_gnl(s2, '\0') + 1);
	if (!p)
	{
		free(s1);
		return (NULL);
	}
	head = p;
	if (s1)
	{
		s_head = s1;
		while (*s1)
			*p++ = *s1++;
		free(s_head);
	}
	if (s2)
		while (*s2)
			*p++ = *s2++;
	*p = '\0';
	return (head);
}

size_t	my_read(int fd, char *buf, char **save)
{
	ssize_t	read_byte;

	read_byte = read(fd, buf, BUFFER_SIZE);
	if (read_byte == 0)
		return (0);
	else if (read_byte == -1)
	{
		free(*save);
		*save = NULL;
		return (0);
	}
	buf[read_byte] = '\0';
	return (read_byte);
}

char	*get_line(char *save, size_t byte_to_nl, size_t byte_to_end)
{
	size_t	byte_to_malloc;
	char	*p;
	char	*head;

	if (!save)
		return (NULL);
	if (!byte_to_nl)
		byte_to_malloc = byte_to_end;
	else
		byte_to_malloc = byte_to_nl;
	p = malloc(sizeof(char) * (byte_to_malloc + 1));
	if (!p)
	{
		free(save);
		return (NULL);
	}
	head = p;
	while (byte_to_malloc--)
		*p++ = *save++;
	*p = '\0';
	return (head);
}

char	*update_save(char *save, char **line, size_t byte_to_nl, size_t len)
{
	char	*p;
	char	*s_head;
	char	*p_head;

	if (!byte_to_nl || (byte_to_nl == len))
	{
		free(save);
		return (NULL);
	}
	p = malloc(sizeof(char) * (len - byte_to_nl + 1));
	if (!p)
	{
		free(save);
		free(*line);
		*line = NULL;
		return (NULL);
	}
	p_head = p;
	s_head = save;
	save = &save[byte_to_nl];
	while (*save)
		*p++ = *save++;
	*p = '\0';
	free(s_head);
	return (p_head);
}
