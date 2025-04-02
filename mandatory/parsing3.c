/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:58:17 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 06:00:03 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	abort_free(t_fdf *data, int y)
{
	while (y >= 0)
	{
		free(data->map[y].line);
		y--;
	}
}

int	populate_every_point(t_fdf data, t_line *array, char *file_name)
{
	char		*line;
	uint32_t	y;
	int			fd;

	y = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (3);
	while (y < data.height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (core_populate(array, line, y))
			return (free(line), abort_free(&data, y), 1);
		free(line);
		y++;
	}
	return (0);
}

uint32_t	get_largest_width(t_fdf *data)
{
	uint32_t	max;
	uint32_t	y;

	max = 0;
	y = 0;
	while (y < data->height)
	{
		if (data->map[y].max_x > max)
			max = data->map[y].max_x;
		y++;
	}
	return (max);
}

void	free_matrix_fdf(int **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

int	locate(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}
