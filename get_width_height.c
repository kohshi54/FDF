#include <stdio.h>
#include <fcntl.h>
#include "LIBFT/get_next_line.h"
#include "LIBFT/libft.h"

size_t	get_height(char *filename)
{
	int		fd;
	size_t	count;

	fd = open(filename, O_RDONLY);
	count = 0;
	while (get_next_line(fd))
		count++;
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

	line_spl = ft_split(line, ' ');
	if (!line_spl)
		exit(EXIT_FAILURE);
	return (count_words(line_spl));
}

size_t	get_width(char *filename)
{
	int		fd;
	size_t	count;
	char	*line;
	size_t	base;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		exit(EXIT_FAILURE);
	base = split_and_count_number_of_words(line);
	while ((line = get_next_line(fd)))
	{
		count = split_and_count_number_of_words(line);
		if (count != base)
		{
			// printf("error map");
			exit(EXIT_FAILURE);
		}
	}
	close(fd);
	return (count);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 		return (0);
// 	printf("%d\n", ft_wc_l(argv[1]));
// 	printf("%d\n", count_width(argv[1]));
// 	return (0);
// }