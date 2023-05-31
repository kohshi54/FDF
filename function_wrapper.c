/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_call_wrapper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:42:06 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/31 18:25:11 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		exit(EXIT_FAILURE);
	return (p);
}

int	ft_open(const char *path, int oflag)
{
	int	fd;

	fd = open(path, oflag);
	if (fd == -1)
		exit(EXIT_FAILURE);
	return (fd);
}

char	**ft_split_wrapper(char *s, char c)
{
	char	**line_spl;

	line_spl = ft_split(s, c);
	free(s);
	if (!line_spl)
		exit(EXIT_FAILURE);
	return (line_spl);
}
