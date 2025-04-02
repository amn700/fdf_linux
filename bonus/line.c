/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 10:06:29 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 04:39:56 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int interpolate_color(int color1, int color2, float t)
{
    int r1 = (color1 >> 24) & 0xFF; 
    int g1 = (color1 >> 16) & 0xFF; 
    int b1 = (color1 >> 8) & 0xFF; 
    int a1 = color1 & 0xFF;        

    int r2 = (color2 >> 24) & 0xFF;
    int g2 = (color2 >> 16) & 0xFF;
    int b2 = (color2 >> 8) & 0xFF;
    int a2 = color2 & 0xFF;

    int r = r1 + t * (r2 - r1);
    int g = g1 + t * (g2 - g1);
    int b = b1 + t * (b2 - b1);
    int a = a1 + t * (a2 - a1);

    return (r << 24) | (g << 16) | (b << 8) | a; 
}

void draw_line(t_screen one, t_screen two, mlx_image_t *img, t_Color_duo c)
{
	t_screen screen;
	float step, i;
	
	screen.x = one.x;
	screen.y = one.y;

	float d_x = two.x - one.x;
	float d_y = two.y - one.y;

	step = (fabs(d_x) > fabs(d_y)) ? fabs(d_x) : fabs(d_y);

	d_x /= step;
	d_y /= step;

	i = 0;
	while (i <= step) 
	{
		float t = (float)i / step;
        int final = interpolate_color(c.color1 , c.color2, t);
		if (screen.x >= 0 && screen.y >= 0 && screen.x < img->width && screen.y < img->height)
	        mlx_put_pixel(img, (int)screen.x, (int)screen.y, final);

		screen.x += d_x;
		screen.y += d_y;
		i++;
	}
}

void	draw_horizontal_line(t_fdf data, int (*color_duo)(int, t_zscale *))

{
	t_screen one;
	t_screen two;
	uint32_t y = 0;
	uint32_t x = 0;

	while (y < data.height)
	{
		x = 0;
		while (x < data.map[y].max_x)
		{
			one = data.map[y].line[x].final;
			if (x + 1 < data.map[y].max_x)
			{
				two = data.map[y].line[x + 1].final;
                if (!color_duo)
				    draw_line(one, two, data.img, (t_Color_duo){data.map[y].line[x].color, data.map[y].line[x + 1].color});
                else
                    draw_line(one, two, data.img,
                        (t_Color_duo)
                        {color_duo(data.map[y].line[x].z, &data.new_zscale),
                            color_duo(data.map[y].line[x+1].z, &data.new_zscale)});
			}
			x++;
		}
		y++;
	}
}

void	draw_vertical_line(t_fdf data, int (*color_duo)(int, t_zscale *))
{
	t_screen one;
	t_screen two;
	uint32_t y = 0;
	uint32_t x = 0;
	while (y < data.height)
	{
		x = 0;
		while (x < data.map[y].max_x)
		{
			one = data.map[y].line[x].final;
			if (y + 1 < data.height)
			{
				two = data.map[y + 1].line[x].final;
                if (!color_duo)
			        draw_line(one, two, data.img, (t_Color_duo){data.map[y].line[x].color, data.map[y + 1].line[x].color});
                else
                    draw_line(one, two, data.img,
                        (t_Color_duo)
                        {color_duo(data.map[y].line[x].z, &data.new_zscale),
                            color_duo(data.map[y+1].line[x].z, &data.new_zscale)});
			}
			x++;
		}
		y++;
	}
}

void	draw_diagnol_line(t_fdf data, int (*color_duo)(int, t_zscale *))
{
	t_screen one;
	t_screen two;
	uint32_t y = 0;
	uint32_t x = 0;
	while (y < data.height)
	{
		x = 0;
		while (x < data.map[y].max_x)
		{
			one = data.map[y].line[x].final;
			if (y + 1 < data.height && x + 1 < data.map[y + 1].max_x)
			{
				two = data.map[y + 1].line[x + 1].final;
                if (!color_duo)
				    draw_line(one, two, data.img, (t_Color_duo){data.map[y].line[x].color, data.map[y + 1].line[x + 1].color});
                else
                draw_line(one, two, data.img,
                    (t_Color_duo)
                    {color_duo(data.map[y].line[x].z, &data.new_zscale),
                        color_duo(data.map[y+1].line[x+1].z, &data.new_zscale)});
			}
			x++;
		}
		y++;
	}	
}

void	draw_diagnol_line_2(t_fdf data, int (*color_duo)(int, t_zscale *))
{
	t_screen one;
	t_screen two;
	uint32_t y = 0;
	uint32_t x = 0;
	while (y + 1 < data.height)
	{
		x = 1;
		while (x < data.map[y].max_x)
		{
			one = data.map[y].line[x].final;
			if (x - 1 < data.map[y + 1].max_x)
			{
				two = data.map[y + 1].line[x - 1].final;
                if (!color_duo)
				    draw_line(one, two, data.img, (t_Color_duo){data.map[y].line[x].color, data.map[y + 1].line[x - 1].color});
                else
                    draw_line(one, two, data.img,
                        (t_Color_duo)
                        {color_duo(data.map[y].line[x].z, &data.new_zscale),
                            color_duo(data.map[y+1].line[x-1].z, &data.new_zscale)});
			}
			x++;
		}
		y++;
	}	
}

void	draw_diagnol_lines(t_fdf data, int (*color_duo)(int, t_zscale *))
{
	draw_diagnol_line(data, color_duo);
	draw_diagnol_line_2(data, color_duo);
}
