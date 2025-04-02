#include "fdf_bonus.h"

int	get_scaled_z(int z, t_zscale *zscale, int scale_min, int scale_max)
{
	float	normalized;

	if (zscale->max == zscale->min)
		return (scale_min);
	// Normalize between 0 and 1
	normalized = (z - zscale->min) / (float)(zscale->max - zscale->min);
	// Ensure that the lowest raw `z` value results in 0 in the scaled version
	return (int)(normalized * (scale_max - scale_min) + 0.5f);
}

void	reduce_scale_range(int *scale_min, int *scale_max)
{
	int	range;

	range = *scale_max - *scale_min;
	if (range <= 1)
	{
		*scale_max = *scale_min; // Allow full reduction to zero
		return ;
	}
	int reduction = (int)(range * 0.1f + 0.5f); // Reduce by 10%, rounded
	if (reduction == 0)
		reduction = 1; // Ensure we always reduce by at least 1
	*scale_max -= reduction;
}

void	increase_scale_range(int *scale_min, int *scale_max)
{
	int	range;

	range = *scale_max - *scale_min;
	int increase = (int)(range * 0.1f + 0.5f); // Increase by 10%, rounded
	// Ensure we always increase scale_max
	if (increase == 0)
		increase = 1;
	*scale_max += increase;
}
