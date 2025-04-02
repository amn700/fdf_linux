/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:10:35 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 06:19:28 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_dims
{
	uint32_t	x;
	uint32_t	y;
}				t_dims;

typedef struct s_screen
{
	double		x;
	double		y;
}				t_screen;

typedef struct s_point
{
	int			z;
	int			color;
	t_screen	final;
}				t_point;

typedef struct s_line
{
	t_point		*line;
	uint32_t	max_x;
}				t_line;

typedef struct s_fdf
{
	mlx_image_t	*img;
	t_line		*map;
	mlx_t		*mlx_ptr;
	uint32_t	width;
	uint32_t	height;
	int			offset_x;
	int			offset_y;
	int			scale_factor;
}				t_fdf;
int				handle_mlx(t_fdf *data);
int				ft_error(int code);
int				parse_map(t_fdf *data, char **argv);
double			to_radians(int degrees);
void			init_struct_fdf(t_fdf *data);
int				check_extention(char *file_name);
int				get_width_and_height(char *file_name, t_fdf *data);
int				count_words(char *str);
int				check_map(int width, char *line);
int				set_max_x_values(char *file_name, t_line *array);
void			abort_free(t_fdf *data, int y);
int				allocate_points(t_fdf *data);
int				locate(const char *s, int c);
int				max(int a, int b);
uint32_t		hexer(char *str, char *upper_base, char *lower_base);
uint32_t		get_color(char *point, int i);
int				ft_atoi_fdf(const char *nptr, int *i);
void			free_matrix_fdf(int **matrix);
int				core_populate(t_line *array, char *line, int y);
int				populate_every_point(t_fdf data, t_line *array,
					char *file_name);
uint32_t		get_largest_width(t_fdf *data);
void			calculate_offsets(t_fdf *data);
int				set_scalefactor(t_fdf *data);
void			draw_horizontal_line(t_fdf data);
void			draw_vertical_line(t_fdf data);
void			render_map(t_fdf *data);
float			ft_step(t_screen *d);
void			draw_line(t_screen one, t_screen two, mlx_image_t *img);
void			ft_draw(t_fdf *data);
int				handle_mlx(t_fdf *data);

#endif