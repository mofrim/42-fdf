/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:31:47 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/26 16:02:48 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Draw line starting from vector a to vector b using mlx_pixel_put. */
void	draw_line_nocolr(t_vec a, t_vec b, t_myxvar myxvar)
{
	double	dx;
	double	dy;
	int		n;
	int		i;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (fabs(dx) >= fabs(dy))
		n = fabs(dx);
	else
		n = fabs(dy);
	dx = dx / (double)n;
	dy = dy / (double)n;
	i = 0;
	while (i <= n)
	{
		mlx_pixel_put(myxvar.mlx, myxvar.win, a.x, a.y, NOCOLR);
		a.x += dx;
		a.y += dy;
		i++;
	}
}

// TODO maybe also adopt to new linedrawing style with vectors as args.
void	draw_line2(t_line line, char *colr, t_myxvar myxvar)
{
	double	dx;
	double	dy;
	int		n;
	int		i;

	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	if (fabs(dx) >= fabs(dy))
		n = fabs(dx);
	else
		n = fabs(dy);
	dx = dx / (double)n;
	dy = dy / (double)n;
	i = 0;
	while (i <= n)
	{
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0, line.y0, \
				rgb_to_int(colr));
		line.x0 += 2 * dx;
		line.y0 += 2 * dy;
		i += 2;
	}
}

// TODO maybe also adopt to new linedrawing style with vectors as args.
void	draw_thick_line(t_line line, char *colr, t_myxvar myxvar)
{
	double	dx;
	double	dy;
	int		n;
	int		i;

	dx = (line.x1 - line.x0);
	dy = (line.y1 - line.y0);
	if (fabs(dx) >= fabs(dy))
		n = fabs(dx);
	else
		n = fabs(dy);
	dx = dx / (double)n;
	dy = dy / (double)n;
	i = 0;
	while (i <= n)
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
