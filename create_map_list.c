// #include "fdf.h"
#include <fcntl.h>
#include <stdio.h>
# include <mlx.h>
# include <unistd.h>
# include <math.h>
# include "LIBFT/libft.h"
# include "LIBFT/ft_printf.h"
# include "LIBFT/get_next_line.h"

typedef	struct s_coordinate
{
	int					x;
	int					y;
	int					z;
	struct s_coordinate	*next;
}	t_coordinate;

typedef	struct s_map
{
	t_coordinate	*head;
	int				range_x;
	int				range_y;
	int				range_z;
}	t_map;

void	free_double_array(char **p)
{
	size_t	i;

	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

void	free_all_node(t_map map)
{
	t_coordinate	*tmp;

	while (map.head)
	{
		tmp = map.head;
		map.head = map.head->next;
		free(tmp);
	}
}

void	print_all_node(t_map map)
{
	while (map.head)
	{
		printf("x: %d, y: %d, z: %d\n", map.head->x, map.head->y, map.head->z);
		if (map.head->next && map.head->next->y != map.head->y)
			printf("###\n");
		map.head = map.head->next;
	}
	printf("x_width: %d, y_width: %d, z_width: %d\n", map.range_x, map.range_y, map.range_z);
}

t_coordinate	*init_node()
{
	t_coordinate	*new;

	new = malloc(sizeof(t_coordinate));
	if (!new)
		exit(EXIT_FAILURE);
	new->x = 0;
	new->y = 0;
	new->z = 0;
	new->next = NULL;
	return (new);
}

t_coordinate	*create_new_node(char **line_spl, int x_count, int y_count, t_coordinate *prev)
{
	t_coordinate *new;

	new = malloc(sizeof(t_coordinate));
	new->x = x_count;
	new->y = y_count;
	new->z = ft_atoi(line_spl[x_count]);
	new->next = NULL;

	prev->next = new;
	return (new);
}

char	**split_line_by_space(char *line)
{
	char	**line_spl;

	line_spl = ft_split(line, ' ');
	free(line);
	return (line_spl);
}

t_coordinate	*add_each_element_to_list(t_map *map, t_coordinate *cur, char **line_spl, int y_count)
{
	int		x_count;

	x_count = 0;
	while (line_spl[x_count] && *(line_spl[x_count]) != '\n')
	{
		cur = create_new_node(line_spl, x_count, y_count, cur);
		if (map->range_x < cur->x)
			map->range_x = cur->x;
		if (map->range_y < cur->y)
			map->range_y = cur->y;
		if (map->range_z < cur->z)
			map->range_z = cur->z;
		x_count++;
	}
	return (cur);
}

void	read_file_and_create_map(t_map *map, int fd)
{
	int				y_count;
	t_coordinate	*cur;
	char			*line;
	char			**line_spl;

	map->head = init_node();
	cur = map->head;
	y_count = 0;
	while ((line = get_next_line(fd)))
	{
		line_spl = split_line_by_space(line);
		cur = add_each_element_to_list(map, cur, line_spl, y_count);
		free_double_array(line_spl);
		y_count++;
	}
}

int	main(int argc, char *argv[])
{
	t_map	map;
	int		fd;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	read_file_and_create_map(&map, fd);
	print_all_node(map);
	free_all_node(map);
	return (0);
}

/*
__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}
*/