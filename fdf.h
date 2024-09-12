/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:39:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/12 20:17:08 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "mlx_int.h"
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
	double x0;
	double y0;
	double x1;
	double y1;
} t_line;

typedef struct s_vec {
	double	x;
	double	y;
	double	z;
} t_vec;

typedef struct s_map {
	t_vec	**vec_map;
	int		cols;
	int		rows;
	int		x_offset;
	int		y_offset;
	int		zoom;
} t_map;

/* Go, collect all the lines to be drawn. */
typedef struct s_linelst {
	t_line				*line;
	struct s_linelst	*next;
} t_linelst;

typedef struct s_myxvar {
	t_xvar *mlx;
	t_win_list *win;
	t_map *orig_map;
	t_map *cur_map;
	int	winsize_x;
	int	winsize_y;
} t_myxvar;

void print_map(t_map *map);
int		rgb_to_int(char *rgbstr);
void	draw_line(t_line line, char *colr, t_myxvar myxvar);
void	draw_thick_line(t_line line, char *colr, t_myxvar myxvar);
t_map	*read_map(char *mapfile);
void	error_exit(void);
void	free_split(char ***split);
void	mult_mat_vec(double a[3][3], t_vec *v);
void	mult_mat_map(double a[3][3], t_map *map);
void 	draw_map_points(t_map *map, char *colr, t_myxvar myxvar);
void 	isometric_proj(t_map *map);
// void 	general_proj(t_myxvar *mxv, double alpha, double beta, double gamma);
void general_proj(t_myxvar **mxv, double alpha, double beta, double gamma);
void	draw_all_the_lines(t_map *map, t_myxvar myxvar);
void	trans_zoom_map(t_map *map, double zoom, int trans_x, int trans_y);
void 	draw_map_fat_points(t_map *map, char *colr, t_myxvar myxvar);
void	mult_mat_by_scalar(double (*a)[3][3], double scalar);
void	free_map(t_map **map);
int		key_win1(int key,t_myxvar *p);
t_map	*duplicate_map(t_map *map);

/* map matrix trafos. */
void	mirro_trafo(t_map *map);
void	right_left_handed_trafo(t_map *map);
void	proj_map_to_xy(t_map *map);
void	rot_map_x(t_map *map, double angl);
void	rot_map_y(t_map *map, double angl);
void	rot_map_z(t_map *map, double angl);

/* linelst funcs. */
void	linelstdelone(t_linelst *node);
void	linelstclear(t_linelst **lst);
t_linelst	*linelstnew(t_line *line);
t_linelst	*linelstlast(t_linelst *head);
void	linelst_add_back(t_linelst **head, t_linelst *newend);


// FIXME remove me / or implement floating point output with ftpr
void	print_mat(double a[3][3]);

#endif
