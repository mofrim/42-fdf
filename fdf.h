/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:39:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/26 17:06:09 by fmaurer          ###   ########.fr       */
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
# include <unistd.h>
# include <fcntl.h>
# include <error.h>

# define WINX 1400
# define WINY 1000
# define MAP_AREA_MINX 300
# define ROTSTP M_PI/12

# define WHITE "ffffff"
# define WHITE2 "aaaaaa"
# define NOCOLR 11184810

// #define FONT "-misc-fixed-*-*-*-*-30-*-*-*-*-*-*-*"
// #define FONT "-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
# define FONT "-misc-fixed-bold-r-normal--18-120-100-100-c-90-iso8859-1"
// #define FONT "-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso8859-1"

typedef struct s_line
{
	double	x0;
	double	y0;
	double	x1;
	double	y1;
}	t_line;

typedef struct s_vec {
	double	x;
	double	y;
	double	z;
	int		colr;
}	t_vec;

typedef struct s_map {
	t_vec	**vec_map;
	int		cols;
	int		rows;
	int		x_offset;
	int		y_offset;
	double	alpha;
	double	beta;
	double	gamma;
	double	zoom;
}	t_map;

typedef struct s_myxvar {
	t_xvar		*mlx;
	t_win_list	*win;
	t_map		*orig_map;
	t_map		*cur_map;
	int			*colrmap;
	int			winsize_x;
	int			winsize_y;
	int			auto_center_map;
	int			show_markers;
	int			marker_size;
	int			mapstyle;
	int			xmin;
	int			xmax;
	int			ymin;
	int			ymax;
	int			zmin;
	int			zmax;
	int			zdiff;
	double		xyfac;
	double		zfac;
}	t_myxvar;

typedef struct s_map_props_bak {
	double	old_zoom;
	int		old_xoff;
	int		old_yoff;
	double	old_alpha;
	double	old_beta;
	double	old_gamma;
}	t_map_props_bak;

/* Datatype in disk drawing. */
typedef struct s_pxl {
	double	x;
	double	y;
}	t_pxl;
/******************************************/

t_myxvar	*init_myxvar(char *mapname);
void		print_map(t_map *map);
void		print_map_without_offset(t_map *map);
void		print_map_nocolr(t_map *map);
int			rgb_to_int(char *rgbstr);
void		draw_line_nocolr(t_vec a, t_vec b, t_myxvar myxvar);
void		draw_thick_line_nocolr(t_vec a, t_vec b, t_myxvar myxvar);
double		*get_next_mapline(int fd, int cols);
t_map		*read_map(char *mapfile);
void		error_exit(char	*msg);
void		nullcheck(void *p, char *msg);
void		free_split(char ***split);
void		mult_mat_vec(double a[3][3], t_vec *v);
void		mult_mat_map(double a[3][3], t_map *map);
void		draw_map_points(t_map *map, char *colr, t_myxvar myxvar);
void		general_proj(t_myxvar **mxv, double alpha, double beta, \
		double gamma);
void		draw_map_nocolr(t_map *map, t_myxvar myxvar);
void		trans_zoom_map(t_map *map, double zoom, int trans_x, int trans_y);
void		draw_map_fat_points(t_map *map, char *colr, t_myxvar myxvar);
void		mult_mat_by_scalar(double (*a)[3][3], double scalar);
void		free_map(t_map **map);
int			key_win1(int key, t_myxvar *p);
t_map		*duplicate_map(t_map *map);
void		resize_map(t_myxvar *mxv, t_map *map, double xyfac, double zfac);
void		initial_resize_map(t_myxvar *mxv, double xyfac, double zfac);
void		draw_map_points_size(t_map *map, t_myxvar myxvar, char *colr, \
		int size);

void		draw_map(t_map *map, t_myxvar mxv, void (*line_draw_func)(t_vec, \
			t_vec, t_myxvar));

int			find_map_x_min(t_map map);
int			find_map_x_max(t_map map);
int			find_map_y_min(t_map map);
int			find_map_y_max(t_map map);
int			find_map_z_min(t_map map);
int			find_map_z_max(t_map map);

/* map matrix trafos. */
void		mirror_trafo(t_map *map);
void		right_left_handed_trafo(t_map *map);
void		proj_map_to_xy(t_map *map);
void		rot_map_x(t_map *map, double angl);
void		rot_map_y(t_map *map, double angl);
void		rot_map_z(t_map *map, double angl);
double		vec_len(t_vec v);
void		scale_height(t_myxvar **mxv, double zfac);
void		center_map(t_myxvar *mxv);
void		draw_disk(t_pxl p, int radius, int colr, t_myxvar mxv);
void		draw_map_disks_size(t_map *map, t_myxvar myxvar, char *colr, \
		int size);
void		show_sidebar(t_myxvar *mxv);

void		int_to_rgb(int rgb_arr[3], int rgb_num);
void		draw_color_line(t_vec a, t_vec b, t_myxvar mxv);
int			*generate_colrmap(t_myxvar mxv);
void		draw_map_color_elev(t_map *map, t_myxvar mxv);
void		draw_line_colr_elev(t_vec a, t_vec b, t_myxvar mxv);

void		stereo_proj(t_myxvar *mxv);
void		cylindr_proj(t_myxvar *mxv);

#endif
