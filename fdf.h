#ifndef FDF_H
# define FDF_H

// # include <mlx.h>
# include "minilibx/mlx.h"
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "LIBFT/libft.h"
# include "LIBFT/ft_printf.h"
# include "LIBFT/get_next_line.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef	struct line_info
{
	int		dx;
	int		dy;
	int		x;
	int		y;
	size_t	deltaA;
	size_t	deltaB;
}	t_line_info	;

typedef	struct s_coordinate
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_coordinate;

typedef struct s_map_info
{
	t_coordinate	***map;
	size_t			height;
	size_t			width;
	size_t			depth;
}	t_map_info;

typedef struct	s_mlx_info {
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_map_info	map_info;
}				t_mlx_info;

int	get_height(char *filename);
int	get_width(char *filename);
void	create_map(char *filename, t_map_info *map_info);
void	print_map(t_coordinate ***map, size_t width, size_t height);
void	draw_map_on_img(t_map_info map_info, t_data img);

# ifndef step
#  define step(a, b) ((a < b) ? 1 : -1);
# endif

void	put_line(t_data *data, t_coordinate start, t_coordinate end, int color);
# ifndef X_WIDTH
#  define X_WIDTH 1920
# endif

# ifndef Y_WIDTH
#  define Y_WIDTH 1080
# endif

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

#endif