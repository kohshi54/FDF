/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:53:00 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/05/31 18:22:08 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct line_info
{
	int		dx;
	int		dy;
	int		x;
	int		y;
	size_t	delta_a;
	size_t	delta_b;
}	t_line_info;

typedef struct s_coordinate
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
	int				origin_x;
	int				origin_y;
	int				scale;
	int				theta_rx;
	double			theta_ry;
	double			theta_rz;
	double			base[3][3];
	bool			axis_flg;
}	t_map_info;

typedef struct s_mlx_info {
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_map_info	map_info;
}	t_mlx_info;

/* get_width_height.c */
size_t			get_height(char *filename);
// int				get_height(char *filename);
size_t			get_width(char *filename);
// int				get_width(char *filename);
void			create_map(char *filename, t_map_info *map_info);
void			print_map(t_coordinate ***map, size_t width, size_t height);
void			draw_map_on_img(t_map_info map_info, t_data img);

void			put_line(t_data *data, t_coordinate start, \
								t_coordinate end, int color);

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

/* rotate_matrix.c */
void			copy_matrix(double dst[3][3], double src[3][3]);
void			rotate_x(double base[3][3], double radian);
void			rotate_y(double base[3][3], double radian);
void			rotate_z(double base[3][3], double radian);

/* set_base.c */
void			set_isometric_base(double base_vector[3][3]);
void			set_standard_base(double base_vector[3][3]);
void			set_inverse_base(double base_vector[3][3]);

/* translation.c */
t_coordinate	move_map_to_win_center(t_coordinate vertex);
t_coordinate	move_map_center_to_origin(t_coordinate vertex, \
						t_map_info map_info);
t_coordinate	move(t_coordinate vertex, int x, int y);
t_coordinate	zoom(t_coordinate vertex, int scale);
t_coordinate	translate(t_coordinate vertex, t_map_info map_info, \
						double base[3][3]);

# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define UP_ARROW 125
# define DOWN_ARROW 126
# define PLUS_KEY 24
# define MINUS_KEY 27
# define X_KEY 7
# define Y_KEY 16
# define Z_KEY 6
# define P_KEY 35
# define I_KEY 34
# define A_KEY 0
# define ESC_KEY 53

/* key_handler_utils.c */
void			parallel_move(int keycode, t_mlx_info *vars);
void			zoom_in_and_out(int keycode, t_mlx_info *vars);
void			rotate_x_y_z(int keycode, t_mlx_info *vars);
void			projection(int keycode, t_mlx_info *vars);
void			axis(int keycode, t_mlx_info *vars);

/* event_handler.c */
int				key_handler(int keycode, t_mlx_info *vars);
int				destory_handler(t_mlx_info *vars);
int				loop_handler(t_mlx_info *mlx_info);

/* init_info.c */
double			set_initial_scale(t_map_info map_info);
void			init_map_info(t_map_info *map_info);
void			init_mlx_info(t_mlx_info *mlx_info, char *filename);

/* draw_map.c */
void			draw_map_on_img(t_map_info map_info, t_data img);

/* free_utils.c */
void			free_split(char **p);

/* system_call_wrapper.c */
void			*ft_malloc(size_t size);
int				ft_open(const char *path, int oflag);
char			**ft_split_wrapper(char *s, char c);

#endif