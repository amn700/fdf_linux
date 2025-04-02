/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:51:34 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 05:52:17 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw(t_fdf *data)
{
	render_map(data);
	draw_horizontal_line(*data);
	draw_vertical_line(*data);
}

float	ft_step(t_screen *d)
{
	if (fabs(d->x) > fabs(d->y))
		return (fabs(d->x));
	return (fabs(d->y));
}

void	draw_line(t_screen one, t_screen two, mlx_image_t *img)
{
	t_screen	screen;
	t_screen	d;
	float		step;
	float		i;

	screen.x = one.x;
	screen.y = one.y;
	d.x = two.x - one.x;
	d.y = two.y - one.y;
	step = ft_step(&d);
	d.x /= step;
	d.y /= step;
	i = 0;
	while (i <= step)
	{
		if (screen.x >= 0 && screen.y >= 0 && screen.x < img->width
			&& screen.y < img->height)
			mlx_put_pixel(img, (int)screen.x, (int)screen.y, -1);
		screen.x += d.x;
		screen.y += d.y;
		i++;
	}
}

void	draw_horizontal_line(t_fdf data)
{
	t_screen	one;
	t_screen	two;
	uint32_t	y;
	uint32_t	x;

	y = 0;
	x = 0;
	while (y < data.height)
	{
		x = 0;
		while (x < data.map[y].max_x)
		{
			one = data.map[y].line[x].final;
			if (x + 1 < data.map[y].max_x)
			{
				two = data.map[y].line[x + 1].final;
				draw_line(one, two, data.img);
			}
			x++;
		}
		y++;
	}
}

void	draw_vertical_line(t_fdf data)
{
	t_screen	one;
	t_screen	two;
	uint32_t	y;
	uint32_t	x;

	y = 0;
	x = 0;
	while (y < data.height)
	{
		x = 0;
		while (x < data.map[y].max_x)
		{
			one = data.map[y].line[x].final;
			if (y + 1 < data.height)
			{
				two = data.map[y + 1].line[x].final;
				draw_line(one, two, data.img);
			}
			x++;
		}
		y++;
	}
}
