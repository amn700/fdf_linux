/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:55:27 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 06:19:14 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_max_x_values(char *file_name, t_line *array)
{
	int		y;
	int		fd;
	char	*line;

	y = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (3);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		array[y++].max_x = count_words(line);
		free(line);
	}
	close(fd);
	return (0);
}

int	allocate_points(t_fdf *data)
{
	uint32_t	y;

	y = 0;
	while (y < data->height)
	{
		if (data->map[y].max_x <= 0)
			return (abort_free(data, y), 2);
		data->map[y].line = calloc(sizeof(t_point), data->map[y].max_x);
		if (!data->map[y].line)
			return (abort_free(data, y), 1);
		y++;
	}
	return (0);
}

u_int32_t	hexer(char *str, char *upper_base, char *lower_base)
{
	int			flag;
	u_int32_t	total;
	int			i;

	i = 0;
	total = 0;
	flag = max(locate(lower_base, str[i]), locate(upper_base, str[i]));
	i++;
	while (flag != -1)
	{
		total = total * 16 + flag;
		flag = max(locate(lower_base, str[i]), locate(upper_base, str[i]));
		i++;
	}
	return (total);
}

u_int32_t	get_color(char *point, int i)
{
	u_int32_t	full_rgba;
	char		*upper_base;
	char		*lower_base;
	int			len;

	upper_base = "0123456789ABCDEF";
	lower_base = "0123456789abcdef";
	if (ft_strncmp(&point[i], ",0x", 3))
		return (0xFFFFFFFF);
	i += 3;
	len = ft_strlen(&point[i]);
	if (point[i + len - 1] == '\n')
		len--;
	full_rgba = hexer(&point[i], upper_base, lower_base);
	if (len == 8)
		return (full_rgba);
	return ((full_rgba << 8) | 0xFF);
}

int	core_populate(t_line *array, char *line, int y)
{
	char		**matrix;
	uint32_t	x;
	int			i;

	x = 0;
	matrix = ft_split(line, 32);
	if (!matrix)
		return (1);
	while (x < array[y].max_x)
	{
		i = 0;
		array[y].line[x].z = ft_atoi_fdf(matrix[x], &i);
		array[y].line[x].color = get_color(matrix[x], i);
		x++;
	}
	free_matrix_fdf((int **)matrix);
	return (0);
}
