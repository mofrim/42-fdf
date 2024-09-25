#include "fdf.h"

// #define FONT "-misc-fixed-*-*-*-*-30-*-*-*-*-*-*-*"
// #define FONT "-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
#define FONT "-misc-fixed-bold-r-normal--18-120-100-100-c-90-iso8859-1"
// #define FONT "-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso8859-1"

int main(int ac, char **av)
{
	t_myxvar *mxv;

	(void)ac;
	mxv = malloc(sizeof(t_myxvar));
	if (!mxv)
		error_exit("malloc of mxv failed");
	mxv->mlx = mlx_init();
	if (!mxv->mlx )
	{
		printf(" !! mlx_init fail !!\n");
		exit(1);
	}
	mxv->win = mlx_new_window(mxv->mlx,WINX,WINY,"fdf");
	if (!mxv->win)
	{
		printf("!! mlx_new_window fail !!\n");
		exit(1);
	}
	mxv->winsize_x = WINX;
	mxv->winsize_y = WINY;
	mxv->auto_center_map = 1;
	mxv->show_markers = 0;
	mxv->marker_size = 4;
	mxv->orig_map = read_map(av[1]);
	initial_resize_map(mxv, 0, 0);
	mxv->orig_map->alpha = 0;
	mxv->orig_map->beta = 0;
	mxv->orig_map->gamma = 0;
	mxv->orig_map->y_offset = 0;
	mxv->orig_map->x_offset = 0;
	mxv->orig_map->zoom = 1;
	mxv->xmax = find_map_x_max(*mxv->orig_map);
	mxv->xmin = find_map_x_min(*mxv->orig_map);
	mxv->ymax = find_map_y_max(*mxv->orig_map);
	mxv->ymin = find_map_y_min(*mxv->orig_map);
	mxv->zmax = find_map_z_max(*mxv->orig_map);
	mxv->zmin = find_map_z_min(*mxv->orig_map);
	mxv->zdiff = mxv->zmax - mxv->zmin;
	mxv->cur_map = duplicate_map(mxv->orig_map);
	mxv->colrmap = generate_colrmap(*mxv);
	center_map(mxv);
	mlx_set_font(mxv->mlx, mxv->win, FONT);
	show_sidebar(mxv);
	draw_map_color_elev(mxv->cur_map, *mxv);
	mlx_key_hook(mxv->win, key_win1, mxv);
	mlx_loop(mxv->mlx);
}

// DEBUG
// 
// ft_printf("\n");
// print_map_without_offset(mxv->cur_map);
// ft_printf("\n");

// DEBUG test conversion
//
// ft_printf("\nint2rgb:\n");
// int rgb[3];
// int_to_rgb(rgb, rgb_to_int("ffffff"));
// ft_printf("int_to_rgb(rgb_to_int(010101)): %d %d %d\n", rgb[0], rgb[1], rgb[2]);
// ft_printf("rgb to int test: %d\n", rgb_to_int("ff"));

// DEBUG color line drawing test
//
// t_vec	a = {a.x = 0, a.y = 0, a.z = 0, a.colr = rgb_to_int("ff0000")};
// t_vec	b = {b.x = 100, b.y = 100, b.z = 0, b.colr = rgb_to_int("00ff00")};
// draw_color_line(a, b, *mxv);

// DEBUG disk drawing test
//
// t_pxl p = { p.x = 512, p.y = 384};
// draw_disk(p, 100, rgb_to_int("00ff00"), *mxv);

// DEBUG colormap
//
// mxv->colrmap = generate_colrmap(*mxv);
// int rgb[3];
// for (int i=0;i <= mxv->zdiff;i++) {
// 	int_to_rgb(rgb, mxv->colrmap[i]);
// 	ft_printf("int_to_rgb(colrmap): %d %d %d\n", rgb[0], rgb[1], rgb[2]);
// }
