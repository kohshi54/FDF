/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width_height.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:53:12 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/31 17:21:33 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	get_height(char *filename)
{
	int		fd;
	size_t	count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		free(line);
		count++;
	}
	close(fd);
	return (count);
}

size_t	count_words(char **line)
{
	int	count;

	count = 0;
	while (*line && **line != '\n')
	{
		count++;
		line++;
	}
	return (count);
}

size_t	split_and_count_number_of_words(char *line)
{
	char	**line_spl;
	size_t	count;

	line_spl = ft_split(line, ' ');
	if (!line_spl)
		exit(EXIT_FAILURE);
	count = count_words(line_spl);
	free_split(line_spl);
	return (count);
}

size_t	get_width(char *filename)
{
	int		fd;
	size_t	count;
	char	*line;
	size_t	base;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	line = get_next_line(fd);
	if (!line)
		exit(EXIT_FAILURE);
	base = split_and_count_number_of_words(line);
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count = split_and_count_number_of_words(line);
		free(line);
		if (count != base)
		{
			ft_printf("error map");
			exit(EXIT_FAILURE);
		}
	}
	close(fd);
	return (count);
}
