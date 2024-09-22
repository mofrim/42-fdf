/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */

/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:17 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/22 20:26:04 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Draw line starting from x to y using mlx_pixel_put. */
void	draw_line(t_line line, char *colr, t_myxvar myxvar)
{
	double	dx;
	double	dy;
	int N;
	int i;

	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	if (fabs(dx) >= fabs(dy))
		N = fabs(dx);
	else
		N = fabs(dy);

	dx = dx / (double)N;
	dy = dy / (double)N;
	i = 0;
	while (i <= N)
	{
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0, line.y0, rgb_to_int(colr));
		line.x0 += dx;
		line.y0 += dy;
		i++;
	}
}

float	g_pixelput_time;
float	g_startTime;
float	g_endTime;

void	draw_line2(t_line line, char *colr, t_myxvar myxvar)
{
	double	dx;
	double	dy;
	int N;
	int i;

	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	if (fabs(dx) >= fabs(dy))
		N = fabs(dx);
	else
		N = fabs(dy);

	dx = dx / (double)N;
	dy = dy / (double)N;
	i = 0;
	while (i <= N)
	{

		// // FIXME remove before sub
		// g_startTime = (float)clock()/CLOCKS_PER_SEC;

		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0, line.y0, rgb_to_int(colr));

		// // FIXME remove before sub
		// g_endTime = (float)clock()/CLOCKS_PER_SEC;
		// g_pixelput_time += g_endTime - g_startTime;
		line.x0 += 2*dx;
		line.y0 += 2*dy;
		i += 2;
	}
}

void	draw_thick_line(t_line line, char *colr, t_myxvar myxvar)
{
	double	dx;
	double	dy;
	int N;
	int i;

	dx = (line.x1 - line.x0);
	dy = (line.y1 - line.y0);
	if (fabs(dx) >= fabs(dy))
		N = fabs(dx);
	else
		N = fabs(dy);
	dx = dx / (double)N;
	dy = dy / (double)N;
	i = 0;
	while (i <= N)
	{
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 , line.y0, rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 - 1, line.y0, rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 + 1, line.y0, rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 , line.y0 - 1, rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 , line.y0 + 1, rgb_to_int(colr));
		line.x0 += dx;
		line.y0 += dy;
		i++;
	}
}
