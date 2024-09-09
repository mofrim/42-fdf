/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:39:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/09 14:32:21 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "mlx.h"
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <unistd.h>

# define WINX 1024
# define WINY 768
# define WHITE "FFFFFF"

typedef struct s_line
{
	int x0;
	int y0;
	int x1;
	int y1;
} t_line;

int	rgb_to_int(char *rgbstr);
void	draw_line(t_line line, char *colr, void *mlx_ptr, void *win_ptr);
	
#endif 
