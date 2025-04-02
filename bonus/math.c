/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 10:13:12 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 04:39:38 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

double	to_radians(int degrees)
{
	return (degrees * M_PI / 180.0);
}
void	rotate_x(double *y, double *z, double theta)
{
	double	temp_y;

	temp_y = *y;
	*y = temp_y * cos(theta) - *z * sin(theta);
	*z = temp_y * sin(theta) + *z * cos(theta);
}

void	rotate_y(double *x, double *z, double theta)
{
	double	temp_x;

	temp_x = *x;
	*x = temp_x * cos(theta) + *z * sin(theta);
	*z = -temp_x * sin(theta) + *z * cos(theta);
}

void	rotate_z(double *x, double *y, double theta)
{
	double	temp_x;

	temp_x = *x;
	*x = temp_x * cos(theta) - *y * sin(theta);
	*y = temp_x * sin(theta) + *y * cos(theta);
}

void	render_map(t_fdf *data)
{
	t_dims	dims;
	double	x;
	double	y;
	double	z;

	dims.y = 0;
	while (dims.y < data->height)
	{
		dims.x = 0;
		while (dims.x < data->map[dims.y].max_x)
		{
			x = (int)dims.x - (int)(data->map[dims.y].max_x / 2);
			y = (int)dims.y - (int)(data->height / 2);
			z = get_scaled_z(data->map[dims.y].line[dims.x].z, &data->zscale,
					data->new_zscale.min, data->new_zscale.max);
			rotate_x(&y, &z, to_radians(data->rotation.x));
			rotate_y(&x, &z, to_radians(data->rotation.y));
			rotate_z(&x, &y, to_radians(data->rotation.z));
			data->map[dims.y].line[dims.x].final.x = (x * (data->scale_factor
						/ 2)) + data->offset_x;
			data->map[dims.y].line[dims.x].final.y = (y * (data->scale_factor
						/ 2)) + data->offset_y;
			dims.x++;
		}
		dims.y++;
	}
}
