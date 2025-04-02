CC = cc
CFLAGS = -Wall -Wextra -Werror
# MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit
NAME = fdf
SRCS = colors.c z_scale.c controls.c fdf_shit.c  line.c math.c  parse_map.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ../libft
GNL_DIR = ../get_next_line
FT_PRINTF_DIR = ../ft_printf
LIBFT = $(LIBFT_DIR)/libft.a
GNL = $(GNL_DIR)/gnl.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
MLX42 = ../MLX42/build/libmlx42.a
# LIBGLFW3 = ./MLX42/libglfw3.a

all: $(LIBFT) $(FT_PRINTF) $(GNL) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF) $(MLX42) $(GNL)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(GNL) $(FT_PRINTF) $(MLX42) -Iinclude -ldl -lglfw -pthread -lm

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	$(MAKE) -C $(GNL_DIR) fclean

re: fclean all

.PHONY: all clean fclean re