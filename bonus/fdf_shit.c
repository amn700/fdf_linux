/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_shit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 04:40:39 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 04:56:47 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	free_fdf_map(t_fdf *data)
{
	uint32_t	y;

	y = 0;
	while (y < data->height)
	{
		free(data->map[y].line);
		y++;
	}
	free(data->map);
}

int	ft_error(int code)
{
	if (code == 1)
		return (write(2, "allocation error\n", 18), 1);
	if (code == 2)
		return (write(2, "invalid line length\n", 20), 1);
	if (code == 3)
		return (write(2, "open error\n", 11), 1);
	if (code == 4)
		return (write(2, "mlx failure\n", 12), 1);
	return (0);
}

int	parse_map(t_fdf *data, char **argv)
{
	int	flag;

	flag = 0;
	flag = get_width_and_height(argv[1], data);
	if (flag > 0)
		return (flag);
	data->map = malloc(sizeof(t_line) * data->height);
	if (!data->map)
		return (1);
	flag = set_max_x_values(argv[1], data->map);
	if (flag > 0)
		return (free(data->map), flag);
	flag = allocate_points(data);
	if (flag > 0)
		return (free(data->map), flag);
	flag = populate_every_point(*data, data->map, argv[1]);
	if (flag > 0)
		return (free_fdf_map(data), flag);
	data->zscale = calculate_zscale(data);
	return (0);
}

void	clean_exit(t_fdf *data, int code)
{
	mlx_delete_texture(data->front_page);
	mlx_delete_image(data->mlx_ptr, data->img);
	mlx_terminate(data->mlx_ptr);
	if (!code)
		exit(1);
	exit(0);
}

void handle_mlx(t_fdf *data)
{
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "fdf_bonus", false);
	if (!data->mlx_ptr)
		return (ft_error(4), free_fdf_map(data), exit(1));
	data->front_page = mlx_load_png("three.png");
	if (!data->front_page)
		return (ft_error(4), free_fdf_map(data), clean_exit(data, 0));
	data->img = mlx_texture_to_image(data->mlx_ptr, data->front_page);
	if (!data->img)
		return (ft_error(4), free_fdf_map(data), clean_exit(data, 0));
	if (mlx_image_to_window(data->mlx_ptr, data->img, 0, 0) < 0)
		return (ft_error(4), free_fdf_map(data), clean_exit(data, 0));
}

int	main(int argc, char **argv)
{
	t_fdf	data;

	if (argc != 2)
		return (write(2, "invalid number of arguments\n", 28), 1);
	init_struct_fdf(&data);
	if (!check_extention(argv[1]))
		return (write(2, "wrong file_extention\n", 21), 1);
	if (ft_error(parse_map(&data, argv)))
		return (1);
	handle_mlx(&data);
	data.scale_factor = set_scalefactor(&data);
	calculate_offsets(&data);
	data.new_zscale = data.zscale;
	mlx_key_hook(data.mlx_ptr, key_handler, &data);
	mlx_loop(data.mlx_ptr);
	return (free_fdf_map(&data), clean_exit(&data, 1), 0);
}
