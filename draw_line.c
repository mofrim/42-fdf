/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */

/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:17 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/09 14:33:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Draw line starting from x to y using mlx_pixel_put. */
void	draw_line(t_line line, char *colr, void *mlx_ptr, void *win_ptr)
{
	double	dx;
	double	dy;
	int N;
	int i;

	dx = fabs((double)line.x1 - (double)line.x0);
	dy = fabs((double)line.y1 - (double)line.y0);
	if (dx >= dy)
		N = dx;
	else
		N = dy;

	dx = dx / N;
	dy = dy / N;
	i = 0;
	while (i < N)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, line.x0, line.y0, rgb_to_int(colr));
		line.x0 += dx;
		line.y0 += dy;
		i++;
	}
}
