/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:47:03 by mohchaib          #+#    #+#             */
/*   Updated: 2025/03/27 05:50:37 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_extention(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name) - 4;
	file_name += len;
	if (!ft_strncmp(file_name, ".fdf", 4))
		return (1);
	return (0);
}

void	init_struct_fdf(t_fdf *data)
{
	data->img = NULL;
	data->height = 0;
	data->width = 0;
	data->offset_x = 0;
	data->offset_y = 0;
	data->scale_factor = 0;
	data->map = NULL;
	data->mlx_ptr = NULL;
}

int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != 32 && !(str[i] >= 9 && str[i] <= 13))
			i++;
	}
	return (count);
}

int	check_map(int width, char *line)
{
	int	count;

	count = count_words(line);
	if (count < width)
		return (ft_printf("Found wrong line length. Exiting."), 0);
	return (1);
}

int	get_width_and_height(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (3);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), (1));
	data->height++;
	data->width = count_words(line);
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!check_map(data->width, line))
			return (free(line), (2));
		data->height++;
		free(line);
	}
	close(fd);
	return (0);
}
