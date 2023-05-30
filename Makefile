NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = fdf.c ft_put_line.c create_map_array.c get_width_height.c
OBJS = $(SRCS:%.c=%.o)

LIBFT = LIBFT/libft.a
LIBFT_DIR = LIBFT/

MLX = libmlx.dylib
MLX_DIR = minilibx/

INCLUDES = fdf.h

LIBRARY = -L./$(LIBFT_DIR) -lft -L./$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(minilibx)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME)

$(LIBFT) : $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

$(minilibx) : $(minilibx_dir)
	$(MAKE) -C $(minilibx_dir)

clean : 
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean : clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY : clean fclean re all