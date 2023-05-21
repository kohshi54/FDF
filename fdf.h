#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <math.h>
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

# ifndef step
#  define step(a, b) ((a < b) ? 1 : -1);
# endif

typedef	struct coordinate
{
	int	x;
	int	y;
	int	z;
}	t_coordinate ;

void	put_line(t_data *data, t_coordinate start, t_coordinate end, int color);
# ifndef X_WIDTH
#  define X_WIDTH 1920
# endif

# ifndef Y_WIDTH
#  define Y_WIDTH 1080
# endif

#endif