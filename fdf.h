#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <unistd.h>
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef	struct line_info
{
	int		dx;
	int		dy;
	int		x;
	int		y;
	size_t	deltaA;
	size_t	deltaB;
}	t_line_info	;

# ifndef step
#  define step(a, b) ((a < b) ? 1 : -1);
# endif

void	put_line(t_data *data, int x0, int y0, int x1, int y1, int color);

#endif