/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:39:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/20 09:53:53 by fmaurer          ###   ########.fr       */
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

# define WHITE "ffffff"
# define WHITE2 "aaaaaa"

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

// TODO go on her tomorrow. angles also need to persist.

typedef struct s_map {
	t_vec	**vec_map;
	int		cols;
	int		rows;
	int		x_offset;
	int		y_offset;
	double	alpha;
	double	beta;
	double	gamma;
	double 	zoom;
	double	xyfac;
	double	zfac;
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

typedef struct s_map_props_bak {
	double	old_zoom;
	int		old_xoff;
	int		old_yoff;
	double	old_alpha;
	double	old_beta;
	double	old_gamma;
} t_map_props_bak;

/* Datatypes for my pointcloud used in circle drawing. */
typedef struct	s_pxl {
	double x;
	double y;
} t_pxl;

typedef struct s_pxlcloud {
	double				x;
	double				y;
	struct s_pxlcloud	*next;
}	t_pxlcloud;
/******************************************/

void	print_map(t_map *map);
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
void	general_proj(t_myxvar **mxv, double alpha, double beta, double gamma);
void	draw_all_the_lines(t_map *map, t_myxvar myxvar);
void	trans_zoom_map(t_map *map, double zoom, int trans_x, int trans_y);
void 	draw_map_fat_points(t_map *map, char *colr, t_myxvar myxvar);
void	mult_mat_by_scalar(double (*a)[3][3], double scalar);
void	free_map(t_map **map);
int		key_win1(int key,t_myxvar *p);
t_map	*duplicate_map(t_map *map);
void	resize_map(t_map *map, double xyfac, double zfac);
void	 initial_resize_map(t_myxvar *mxv, double xyfac, double zfac);
void	draw_map_points_size(t_map *map, t_myxvar myxvar, char *colr, int size);

/* map matrix trafos. */
void	mirror_trafo(t_map *map);
void	right_left_handed_trafo(t_map *map);
void	proj_map_to_xy(t_map *map);
void	rot_map_x(t_map *map, double angl);
void	rot_map_y(t_map *map, double angl);
void	rot_map_z(t_map *map, double angl);
double	vec_len(t_vec v);
void	scale_height(t_myxvar **mxv, double zfac);

/* linelst funcs. */
void		linelstdelone(t_linelst *node);
void		linelstclear(t_linelst **lst);
t_linelst	*linelstnew(t_line *line);
t_linelst	*linelstlast(t_linelst *head);
void		linelst_add_back(t_linelst **head, t_linelst *newend);

/* Pixelcloud functions. */
void		pxcl_add_back(t_pxlcloud **head, t_pxlcloud *newend);
t_pxlcloud	*pxcl_last(t_pxlcloud *head);
t_pxlcloud	*pxcl_new(double x, double y);
void		pxcl_clear(t_pxlcloud **p);
void		pxcl_delone(t_pxlcloud *node);
void		draw_disk(t_pxl p, int radius, char *colr, t_myxvar mxv);
void		draw_map_disks_size(t_map *map, t_myxvar myxvar, char *colr, int size);
void		pxcl_print_size(t_pxlcloud *p);


// FIXME remove me / or implement floating point output with ftpr
void	print_mat(double a[3][3]);

#endif
