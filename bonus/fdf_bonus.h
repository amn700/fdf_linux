#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_dims
{
	uint32_t		x;
	uint32_t		y;
}					t_dims;

typedef struct s_Color_duo
{
	uint32_t		color1;
	uint32_t		color2;
}					t_Color_duo;

typedef struct s_screen
{
	double			x;
	double			y;
}					t_screen;

typedef struct s_isom
{
	double			cos;
	double			sin;
}					t_isom;

typedef struct s_offset
{
	int				x;
	int				y;
}					t_offset;

typedef struct s_point
{
	int				z;
	int				color;
	t_screen		final;
}					t_point;

typedef struct s_line
{
	t_point			*line;
	uint32_t		max_x;
}					t_line;

typedef struct s_rotation
{
	double			x;
	double			y;
	double			z;
}					t_rotation;

typedef struct s_zscale
{
	int				min;
	int				max;
}					t_zscale;

typedef struct s_rgba
{
	int 			r;
	int 			g;
	int 			b;
	int 			a;
}					t_rgba;

typedef struct s_fdf
{
	mlx_t			*mlx_ptr;
	mlx_image_t		*img;
	mlx_image_t		*menu[24];
	int 			show_menu;
	t_line			*map;
	mlx_texture_t	*front_page;
	t_rotation		rotation;
	uint32_t		width;
	uint32_t		height;
	int				angle;
	int				offset_x;
	int				offset_y;
	int				scale_factor;
	int				diagnol_lines;
	t_zscale		zscale;
	t_zscale 		new_zscale;
	int 			parallel;
	int				(*color_func)(int, t_zscale *);
}					t_fdf;


int ice_fire(int z, t_zscale *zscale);
int purple_green(int z, t_zscale *zscale);
int gold_teal(int z, t_zscale *zscale);
int neon_pink_cyan(int z, t_zscale *zscale);
int sepia(int z, t_zscale *zscale);
int warm_cool(int z, t_zscale *zscale);
int classic_black_white(int z, t_zscale *zscale);

void 				reduce_scale_range(int *scale_min, int *scale_max);
void 				increase_scale_range(int *scale_min, int *scale_max);
int 				get_scaled_z(int z, t_zscale *zscale, int scale_min, int scale_max);
t_zscale 			calculate_zscale(t_fdf *data);
int					ft_error(int code);
void				calculate_offsets(t_fdf *data);
int					set_scalefactor(t_fdf *data);
void				free_fdf_map(t_fdf *data);
void				clean_exit(t_fdf *data, int code);
void				control(t_fdf *data, mlx_key_data_t keydata);
void				scale(t_fdf *data, mlx_key_data_t keydata);
void				rotations(t_fdf *data, mlx_key_data_t keydata);
void				key_handler(mlx_key_data_t keydata, void *param);
int					interpolate_color(int color1, int color2, float t);
void				draw_line(t_screen one, t_screen two, mlx_image_t *img,
						t_Color_duo c);
// void				draw_horizontal_line(t_fdf data, int mode);
// void				draw_vertical_line(t_fdf data, int mode);
// void				draw_diagnol_lines(t_fdf data, int mode);
double				to_radians(int degrees);
void				rotate_x(double *y, double *z, double theta);
void				rotate_y(double *x, double *z, double theta);
void				rotate_z(double *x, double *y, double theta);
void				render_map(t_fdf *data);

uint32_t			get_largest_width(t_fdf *data);

void				free_matrix_fdf(int **matrix);
int					check_extention(char *file_name);
int					set_max_x_values(char *file_name, t_line *array);

int					allocate_points(t_fdf *data);
int					populate_every_point(t_fdf data, t_line *array,
						char *file_name);
int					ft_atoi_fdf(const char *nptr, int *i);
int					locate(const char *s, int c);
int					max(int a, int b);
uint32_t			hexer(char *str, char *upper_base, char *lower_base);
uint32_t			get_color(char *point, int i);
int					count_words(char *str);
int					check_map(int width, char *line);
int					get_width_and_height(char *file_name, t_fdf *data);
void				init_struct_fdf(t_fdf *data);


void	draw_horizontal_line(t_fdf data, int (*color_duo)(int, t_zscale *));
void	draw_vertical_line(t_fdf data, int (*color_duo)(int, t_zscale *));
void	draw_diagnol_line(t_fdf data, int (*color_duo)(int, t_zscale *));
void	draw_diagnol_line_2(t_fdf data,int (*color_duo)(int, t_zscale *));
void	draw_diagnol_lines(t_fdf data, int (*color_duo)(int, t_zscale *));

#endif