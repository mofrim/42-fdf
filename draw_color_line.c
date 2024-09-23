/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:10:44 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/23 11:50:31 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

int	interpolate_color(int start, int end, double step);

void	draw_color_line(t_vec a, t_vec b, t_myxvar mxv)
{
	double	dx;
	double	dy;
	int		N;
	int		i;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (fabs(dx) >= fabs(dy))
		N = fabs(dx);
	else
		N = fabs(dy);

	dx = dx / (double)N;
	dy = dy / (double)N;
	i = 0;
	while (i <= N)
	{
		mlx_pixel_put(mxv.mlx, mxv.win, a.x, a.y, \
				interpolate_color(a.colr, b.colr, ((double)i)/N));
		a.x += dx;
		a.y += dy;
		i++;
	}
}

int	interpolate_color(int start, int end, double step)
{
	int	rgb_start[3];
	int	rgb_end[3];
	int	current_colr;

	if (start == end)
		return (start);
	current_colr = 0;
	current_colr |= rgb_start[0] + (int)((rgb_end[0] - rgb_start[0]) * step);
	current_colr <<= 8;
	current_colr |= rgb_start[1] + (int)((rgb_end[1] - rgb_start[1]) * step);
	current_colr <<= 8;
	current_colr |= rgb_start[2] + (int)((rgb_end[2] - rgb_start[2]) * step);
	return (current_colr);
}
