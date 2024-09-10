/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:39:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/09 23:35:00 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft/libft.h"

# include <math.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <error.h>


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

typedef struct s_vec {
	int	x;
	int	y;
	int z;
} t_vec;

typedef struct s_map {
	t_vec	**vec_map;
	int		cols;
	int		rows;
} t_map;

/* Go, collect all the lines to be drawn. */
typedef struct s_line_lst {
	t_line	*line;
	t_line	*next;
} t_line_lst;


void print_map(t_map *map);
int		rgb_to_int(char *rgbstr);
void	draw_line(t_line line, char *colr, void *mlx_ptr, void *win_ptr);
void	draw_thick_line(t_line line, char *colr, void *mlx_ptr, void *win_ptr);
t_map	*read_map(char *mapfile);
void	error_exit(void);
void	free_split(char ***split);
	
#endif 
