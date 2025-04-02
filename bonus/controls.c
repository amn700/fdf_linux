/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:13:47 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 04:40:49 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	control(t_fdf *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_UP)
		data->offset_y -= 50;
	if (keydata.key == MLX_KEY_DOWN)
		data->offset_y += 50;
	if (keydata.key == MLX_KEY_LEFT)
		data->offset_x -= 50;
	if (keydata.key == MLX_KEY_RIGHT)
		data->offset_x += 50;
}

void	scale(t_fdf *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_I)
		data->scale_factor += 2;
	if (keydata.key == MLX_KEY_O && data->scale_factor > 2)
		data->scale_factor -= 2;
}

void	rotations(t_fdf *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_1)
		data->rotation.z += 5;
	if (keydata.key == MLX_KEY_2)
		data->rotation.z -= 5;
	if (keydata.key == MLX_KEY_4)
		data->rotation.y += 5;
	if (keydata.key == MLX_KEY_5)
		data->rotation.y -= 5;
	if (keydata.key == MLX_KEY_7)
		data->rotation.x += 5;
	if (keydata.key == MLX_KEY_8)
		data->rotation.x -= 5;
}

int	reset_image(t_fdf *data)
{
	mlx_delete_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img)
		return (1);
	if (mlx_image_to_window(data->mlx_ptr, data->img, 0, 0) < 0)
		return (1);
	return (0);
}
void	z_scalling(t_fdf *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_P)
	{
		data->parallel = !data->parallel;
		data->new_zscale.max = 0;
		data->new_zscale.min = 0;
	}
	if (keydata.key == MLX_KEY_R)
		data->new_zscale = data->zscale;
	if (keydata.key == MLX_KEY_KP_ADD)
		increase_scale_range(&data->new_zscale.min, &data->new_zscale.max);
	if (keydata.key == MLX_KEY_KP_SUBTRACT)
		reduce_scale_range(&data->new_zscale.min, &data->new_zscale.max);
}
void	draw_text(t_fdf *data, int x, int y, const char *text)
{
	mlx_put_string(data->mlx_ptr, text, x, y);
}

void	draw_menu(t_fdf *data)
{
	int	menu_width;
	int	menu_x;
	int	y;

	menu_width = WIDTH / 5;
	menu_x = WIDTH - menu_width + 75;
	y = 25;
	data->menu[0] = mlx_put_string(data->mlx_ptr, "------>CONTROLS<------",
			menu_x + 10, y);
	data->menu[1] = mlx_put_string(data->mlx_ptr, "move: UP/DOWN/LEFT/RIGHT",
			menu_x + 10, y + 50);
	data->menu[2] = mlx_put_string(data->mlx_ptr, "-------->ZOOM<--------",
			menu_x + 10, y + 100);
	data->menu[3] = mlx_put_string(data->mlx_ptr, "zoom in:  I", menu_x + 60, y
			+ 150);
	data->menu[4] = mlx_put_string(data->mlx_ptr, "zoom out: O", menu_x + 60, y
			+ 175);
	data->menu[5] = mlx_put_string(data->mlx_ptr, "------->Z SCALE<------",
			menu_x + 10, y + 225);
	data->menu[6] = mlx_put_string(data->mlx_ptr, "increase scale: +", menu_x
			+ 50, y + 275);
	data->menu[7] = mlx_put_string(data->mlx_ptr, "decrease scale: -", menu_x
			+ 50, y + 300);
	data->menu[9] = mlx_put_string(data->mlx_ptr, "------>ROTATIONS<-----",
			menu_x + 10, y + 350);
	data->menu[10] = mlx_put_string(data->mlx_ptr, "x axis rotation: 1/2",
			menu_x + 30, y + 400);
	data->menu[11] = mlx_put_string(data->mlx_ptr, "y axis rotation: 4/5",
			menu_x + 30, y + 425);
	data->menu[12] = mlx_put_string(data->mlx_ptr, "z axis rotation: 7/8",
			menu_x + 30, y + 475);
	data->menu[13] = mlx_put_string(data->mlx_ptr, "---->DIAGNOL LINES<---",
			menu_x + 10, y + 525);
	data->menu[14] = mlx_put_string(data->mlx_ptr, "toggle :T", menu_x + 70, y
			+ 575);
	data->menu[15] = mlx_put_string(data->mlx_ptr, "-------->MENU<--------",
			menu_x + 10, y + 625);
	data->menu[16] = mlx_put_string(data->mlx_ptr, "toogle: ENTER", menu_x + 60,
			y + 675);
	data->menu[17] = mlx_put_string(data->mlx_ptr, "----->PROJECTION<-----",
			menu_x + 10, y + 725);
	data->menu[18] = mlx_put_string(data->mlx_ptr, "parallel: P", menu_x + 70, y
			+ 775);
	data->menu[19] = mlx_put_string(data->mlx_ptr, "isometric: R", menu_x + 70,
			y + 825);
	data->menu[20] = mlx_put_string(data->mlx_ptr, "-------->EXIT<--------",
			menu_x + 10, y + 875);
	data->menu[21] = mlx_put_string(data->mlx_ptr, "exit: ESC", menu_x + 70, y
			+ 925);
	data->menu[22] = mlx_put_string(data->mlx_ptr,
			"------------------------------------>COLORS<------------------------------------",
			WIDTH / 7, y + 900);
	data->menu[23] = mlx_put_string(data->mlx_ptr, "black/white: C || sepia: X|| ice/fire: C || purple/green: V || gold/teal: B|| neonpink/cyan: M || warm/cool: N || reset: SPACE ", 50, y + 940);
}

void	duo_coloring(t_fdf *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_SPACE)
		data->color_func = NULL;
	if (keydata.key == MLX_KEY_Z)
		data->color_func = classic_black_white;
	if (keydata.key == MLX_KEY_X)
		data->color_func = sepia;
	if (keydata.key == MLX_KEY_C)
		data->color_func = ice_fire;
	if (keydata.key == MLX_KEY_V)
		data->color_func = purple_green;
	if (keydata.key == MLX_KEY_B)
		data->color_func = gold_teal;
	if (keydata.key == MLX_KEY_N)
		data->color_func = neon_pink_cyan;
	if (keydata.key == MLX_KEY_M)
		data->color_func = warm_cool;
}

void	delete_menu(t_fdf *data)
{
	int	i;

	i = 0;
	while (i < 24)
	{
		if (data->menu[i])
		{
			mlx_delete_image(data->mlx_ptr, data->menu[i]);
			data->menu[i] = NULL;
		}
		i++;
	}
}
void	menu(t_fdf *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_ENTER)
	{
		data->show_menu = !data->show_menu;
		if (data->show_menu)
			draw_menu(data);
		else
			delete_menu(data);
	}
}
void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_fdf	*data;

	data = (t_fdf *)param;
	if (keydata.action == MLX_PRESS)
	{
		menu(data, keydata);
		if (keydata.key == MLX_KEY_ESCAPE)
			return (free_fdf_map(data), clean_exit(data, 1));
		if (keydata.key == MLX_KEY_T)
			data->diagnol_lines = !data->diagnol_lines;
		duo_coloring(data, keydata);
		z_scalling(data, keydata);
		control(data, keydata);
		scale(data, keydata);
		rotations(data, keydata);
	}
	if (reset_image(data))
		return (ft_error(4), free_fdf_map(data), clean_exit(data, 1));
	render_map(data);
	draw_horizontal_line(*data, data->color_func);
	draw_vertical_line(*data, data->color_func);
	if (data->diagnol_lines)
		draw_diagnol_lines(*data, data->color_func);
}
