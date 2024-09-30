/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:39:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 22:33:19 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>
# include <error.h>

# define WINX 1400
# define WINY 1000
// # define WINX 1400
// # define WINY 1000
# define MAP_AREA_MINX 300

# define WHITE "ffffff"
# define WHITE2 "aaaaaa"
# define NOCOLR 11184810

// #define FONT "-misc-fixed-*-*-*-*-30-*-*-*-*-*-*-*"
// #define FONT "-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
# define FONT "-misc-fixed-bold-r-normal--18-120-100-100-c-90-iso8859-1"
// #define FONT "-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso8859-1"

/* A 3D Vector. Extra fields for storing initial z-values and saving colors from
 * mapfile. */
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
	double	zo;
	int		colr;
}	t_vec;

typedef struct s_anglst
{
	double			a;
	double			b;
	double			g;
	struct s_anglst	*next;
}	t_anglst;

/* Holds all map-specific info. */
typedef struct s_map
{
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

/* The master xvar. */
typedef struct s_myxvar
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_map		*orig_map;
	t_map		*cur_map;
	t_anglst	*anglst;
	int			*colrmap;
	int			winsize_x;
	int			winsize_y;
	int			auto_center_map;
	int			show_markers;
	int			marker_size;
	int			markerstyle;
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

/* Backup struct for map-params. */
typedef struct s_map_props_bak
{
	double	old_zoom;
	int		old_xoff;
	int		old_yoff;
	double	old_alpha;
	double	old_beta;
	double	old_gamma;
}	t_map_props_bak;

/* Datatype in disk drawing. */
typedef struct s_pxl
{
	double	x;
	double	y;
}	t_pxl;

/* Init myxvar. */
t_myxvar	*init_myxvar(char *mapname);

/* Map reading / helper functions. */
void		print_map(t_map *map);
void		print_map_without_offset(t_map *map);
void		print_map_nocolr(t_map *map);
void		print_map_nocolr_z(t_map *map);
double		*get_next_mapline(int fd, int cols);
t_map		*read_map(char *mapfile);
void		free_map(t_map **map);
t_map		*duplicate_map(t_map *map);

/* Drawing functions. */
void		draw_disk(t_pxl p, int radius, int colr, t_myxvar mx);
void		draw_map_disks_size_colr_elev(t_map *map, t_myxvar mx, int size);
void		draw_map_disks_size(t_map *map, t_myxvar myxvar, int size);
void		draw_map(t_map *map, t_myxvar mx, void (*line_draw_func)(t_vec, \
			t_vec, t_myxvar));
void		draw_line_nocolr(t_vec a, t_vec b, t_myxvar mx);
void		draw_thick_line_nocolr(t_vec a, t_vec b, t_myxvar mx);
void		draw_color_line(t_vec a, t_vec b, t_myxvar mx);
void		draw_line_colr_elev(t_vec a, t_vec b, t_myxvar mx);
void		draw_fat_line_colr_elev(t_vec a, t_vec b, t_myxvar mx);
void		put_fat_pixel(int x, int y, t_myxvar mx, int colr);

/* Matrix / Vector operations. */
void		mult_mat_vec(double a[3][3], t_vec *v);
void		mult_mat_by_scalar(double (*a)[3][3], double scalar);
void		mult_mat_map(double a[3][3], t_map *map);
double		vec_len(t_vec v);

/* Map trafos. */
void		resize_map(t_myxvar *mx, t_map *map, double xyfac, double zfac);
void		initial_resize_map(t_myxvar *mx);
void		rotate_map(t_myxvar *mx, double alpha, double beta, \
							double gamma);
void		rotate_map_replay(t_myxvar *mx, double alpha, double beta, \
								double gamma);
void		trans_zoom_map(t_map *map, double zoom, int trans_x, int trans_y);
void		mirror_trafo(t_map *map);
void		right_left_handed_trafo(t_map *map);
void		proj_map_to_xy(t_map *map);
void		rot_map_x(t_map *map, double angl);
void		rot_map_y(t_map *map, double angl);
void		rot_map_z(t_map *map, double angl);
void		scale_height(t_myxvar *mx, double zfac);
void		center_map(t_myxvar *mx);
void		reset_map(t_myxvar *mx);
void		mirror_z_map(t_map *map);

/* Sidebar functions. */
void		show_sidebar(t_myxvar *mx);
void		print_menu_text(t_myxvar *mx, int x, int y, char *txt);
void		print_mapinfo_float(t_myxvar *mx, const char *txt, double prop, \
								int *i);

/* Interactive functions. */
int			kbd_input_handler(int key, t_myxvar *p);
void		redraw_map(t_myxvar *mx);
void		handle_arrow_keys(int key, t_myxvar *p);
void		handle_rotation_keys(int key, t_myxvar *p);
void		handle_zoom_keys(int key, t_myxvar *p);
void		handle_quit_destroy_keys(int key, t_myxvar *p);
void		handle_scale_height_keys(int key, t_myxvar *p);
void		handle_center_key(int key, t_myxvar *p);
void		handle_reset_key(int key, t_myxvar *p);
void		handle_debug_key(int key, t_myxvar *p);
void		show_iso_proj(t_myxvar *p);
void		handle_marker_keys(int key, t_myxvar *p);
void		handle_mapstyle_keys(int key, t_myxvar *p);
void		handle_markerstyle_keys(int key, t_myxvar *mx);

/* Utils. Of any kind. */
void		int_to_rgb(int rgb_arr[3], int rgb_num);
int			rgb_to_int(char *rgbstr);
int			*generate_colrmap(t_myxvar mx);
int			get_elev_colr(int z, t_myxvar mxv);
int			find_map_x_min(t_map map);
int			find_map_x_max(t_map map);
int			find_map_y_min(t_map map);
int			find_map_y_max(t_map map);
int			find_map_z_min(t_map map);
int			find_map_z_max(t_map map);
void		error_exit(char	*msg);
void		nullcheck(void *p, char *msg);
void		free_split(char ***split);
int			close_btn_handler(t_myxvar *mx);
char		*float_string(double d);

/* angl lst. */

void		anglstclear(t_anglst **lst);
t_anglst	*anglstnew(double a, double b, double g);
t_anglst	*anglstlast(t_anglst *head);
void		anglst_add_back(t_anglst **head, t_anglst *newend);
void		print_anglst(t_anglst *head);

#endif
