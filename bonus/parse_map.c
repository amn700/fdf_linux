#include "fdf_bonus.h"

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

void	calculate_offsets(t_fdf *data)
{
	data->offset_x = (int)(WIDTH - data->scale_factor) / 2;
	data->offset_y = (int)(HEIGHT - data->scale_factor) / 2;
}

t_zscale	calculate_zscale(t_fdf *data)
{
	t_zscale	zscale;
	uint32_t	x;
	uint32_t	y;
	int			z;

	zscale.min = INT_MAX;
	zscale.max = INT_MIN;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->map[y].max_x)
		{
			z = data->map[y].line[x].z;
			if (z > zscale.max)
				zscale.max = z;
			if (z < zscale.min)
				zscale.min = z;
			x++;
		}
		y++;
	}
	return (zscale);
}

int	set_scalefactor(t_fdf *data)
{
	double	scale_x;
	double	scale_y;
	double	largest_width;

	largest_width = (double)get_largest_width(data);
	scale_x = WIDTH / (largest_width + 2);
	scale_y = HEIGHT / (data->height + 2);
	if (scale_x > scale_y)
		return ((int)scale_x);
	return ((int)scale_y);
}

void	free_matrix_fdf(int **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

int	check_extention(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name) - 4;
	file_name += len;
	if (!ft_strncmp(file_name, ".fdf", 4))
		return (1);
	return (0);
}

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

static void	abort_free(t_fdf *data, int y)
{
	while (y >= 0)
	{
		free(data->map[y].line);
		y--;
	}
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

int	max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}
uint32_t	hexer(char *str, char *upper_base, char *lower_base)
{
	int			flag;
	uint32_t	total;
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

uint32_t	get_color(char *point, int i)
{
	uint32_t	full_rgba;
	char		*upper_base;
	char		*lower_base;
	int			len;

	upper_base = "0123456789ABCDEF";
	lower_base = "0123456789abcdef";
	if (ft_strncmp(&point[i], ",0x", 3))
		return (0xFFFFFFFF);
	i += 3;
	// Parse the color value (e.g., 3 parts for RGB)
	len = ft_strlen(&point[i]);
	if (point[i + len - 1] == '\n')
		len--;
	full_rgba = hexer(&point[i], upper_base, lower_base);
	if (len == 8)
		return (full_rgba);
	return ((full_rgba << 8) | 0xFF);
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
	int		count;
	int		fd;
	char	*line;

	count = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (3);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), (1));
	count++;
	data->width = count_words(line);
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!check_map(data->width, line))
			return (free(line), (2));
		count++;
		free(line);
	}
	data->height = count;
	close(fd);
	return (0);
}

void	init_struct_fdf(t_fdf *data)
{
	data->parallel = 0;
	data->show_menu = 0;
	data->color_func = NULL;
	data->front_page = NULL;
	data->img = NULL;
	data->height = 0;
	data->width = 0;
	data->angle = 0;
	data->offset_x = 0;
	data->offset_y = 0;
	data->scale_factor = 0;
	data->diagnol_lines = 0;
	data->rotation.x = 35.264;
	data->rotation.y = -45;
	data->rotation.z = 0;
	data->map = NULL;
	data->mlx_ptr = NULL;
}
