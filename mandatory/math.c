/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 06:00:25 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 06:34:14 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	to_radians(int degrees)
{
	return (degrees * M_PI / 180.0);
}

int	max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

void	calculate_offsets(t_fdf *data)
{
	data->offset_x = (int)(WIDTH - data->scale_factor) / 2;
	data->offset_y = (int)(HEIGHT - data->scale_factor) / 2;
}

int	set_scalefactor(t_fdf *data)
{
	double	scale_x;
	double	scale_y;
	double	largest_width;

	largest_width = (double)get_largest_width(data);
	scale_x = WIDTH / (largest_width + 2);
	scale_y = HEIGHT / (data->height + 2);
	if (scale_x < scale_y)
		return ((int)scale_x);
	return ((int)scale_y);
}

void	render_map(t_fdf *data)
{
	t_dims		dims;
	t_screen	screen;

	dims.y = 0;
	while (dims.y < data->height)
	{
		dims.x = 0;
		while (dims.x < data->map[dims.y].max_x)
		{
			screen.x = (int)(dims.x - dims.y) *cos(to_radians(25));
			screen.y = (dims.x + dims.y) * sin(to_radians(25))
				- data->map[dims.y].line[dims.x].z;
			data->map[dims.y].line[dims.x].final.x = (screen.x
					* (data->scale_factor / 2)) + data->offset_x;
			data->map[dims.y].line[dims.x].final.y = (screen.y
					* (data->scale_factor / 2)) + data->offset_y;
			dims.x++;
		}
		dims.y++;
	}
}
