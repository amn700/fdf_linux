/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 04:41:21 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 06:33:19 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_mlx(t_fdf *data)
{
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "fdf", false);
	if (!data->mlx_ptr)
		return (0);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img)
		return (0);
	return (1);
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
	return (0);
}
