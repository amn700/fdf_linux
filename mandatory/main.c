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

int	ft_atoi_fdf(const char *nptr, int *i)
{
	int	sign;
	int	total;

	sign = 1;
	total = 0;
	while (nptr[*i] == 32 || (nptr[*i] >= 9 && nptr[*i] <= 13))
		(*i)++;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			sign = -1;
		(*i)++;
	}
	while (nptr[*i] >= '0' && nptr[*i] <= '9')
	{
		total = total * 10 + (nptr[*i] - '0');
		(*i)++;
	}
	return (total * sign);
}

void	clean_exit(t_fdf *data, int code)
{
	mlx_delete_image(data->mlx_ptr, data->img);
	mlx_terminate(data->mlx_ptr);
	if (!code)
		exit(1);
	exit(0);
}

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

void	keys(mlx_key_data_t keydata, void *param)
{
	t_fdf	*data;

	data = (t_fdf *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			return (free_fdf_map(data), clean_exit(data, 1));
	}
}

int	main(int argc, char **argv)
{
	t_fdf	data;

	if (argc != 2)
		return (write(2, "error1\n", 7), 1);
	init_struct_fdf(&data);
	if (!check_extention(argv[1]))
		return (write(2, "wrong file_extention\n", 21), 1);
	if (ft_error(parse_map(&data, argv)))
		return (1);
	if (!handle_mlx(&data))
		return (ft_error(4), free_fdf_map(&data), clean_exit(&data, 0), 1);
	if (mlx_image_to_window(data.mlx_ptr, data.img, 0, 0) < 0)
		return (ft_error(4), free_fdf_map(&data), clean_exit(&data, 0), 1);
	data.scale_factor = set_scalefactor(&data);
	calculate_offsets(&data);
	ft_draw(&data);
	mlx_key_hook(data.mlx_ptr, keys, &data);
	mlx_loop(data.mlx_ptr);
	return (free_fdf_map(&data), clean_exit(&data, 1), 0);
}
