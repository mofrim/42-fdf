// TODO test this in a ubuntu VM!

#include "fdf.h"
#include "mlx_int.h"

// #define FONT "-misc-fixed-*-*-*-*-30-*-*-*-*-*-*-*"
#define FONT "-*-*-*-*-*-*-*-*-*-*-*-*-*-*"

void	mat_mult_test(void);

int main(int ac, char **av)
{
	// main1();

	t_xvar *mlx;
	t_win_list *win1;
	t_map	*map;
	t_myxvar *mxv;

	(void)ac;
	mlx = mlx_init();
	if (!mlx )
	{
		printf(" !! mlx_init fail !!\n");
		exit(1);
	}
	win1 = mlx_new_window(mlx,WINX,WINY,"fdf");
	if (!win1)
	{
		printf("!! mlx_new_window fail !!\n");
		exit(1);
	}

	// TODO write an mxv init function!!!
	mxv = malloc(sizeof(t_myxvar));
	if (!mxv)
		error_exit();
	mxv->mlx = mlx;
	mxv->win = win1;
	mxv->winsize_x = WINX;
	mxv->winsize_y = WINY;
	mxv->orig_map = read_map(av[1]);
	initial_resize_map(mxv);
	mxv->orig_map->alpha = 0;
	mxv->orig_map->beta = 0;
	mxv->orig_map->gamma = 0;
	mxv->orig_map->y_offset = 0;
	mxv->orig_map->x_offset = 0;
	mxv->orig_map->zoom = 1;
	mxv->cur_map = duplicate_map(mxv->orig_map);

	ft_printf("\n");
	print_map(mxv->cur_map);
	ft_printf("\n");
	// trans_zoom_map(mxv->cur_map, 1, mxv->winsize_x/4, mxv->winsize_y/2);
	ft_printf("zoom, xoff, yoff = %d, %d, %d\n", mxv->cur_map->zoom, mxv->cur_map->x_offset, mxv->cur_map->y_offset);
	draw_all_the_lines(mxv->cur_map, *mxv);
	draw_map_fat_points(mxv->cur_map, "00FF00", *mxv);

	// NOTE line drawing test
	//
	// t_line line;
	// line.x0 = 20;
	// line.y0 = 0;
	// line.x1 = 20;
	// line.y1 = -768;
	// draw_thick_line(line, WHITE, *mxv);

	mat_mult_test();
	mlx_key_hook(win1,key_win1, mxv);
	mlx_loop(mlx);
}

void	main1(void)
{
	void *mlx;
	void *win1;
	// int	i;
	// int	color;
	t_line line;
	t_myxvar myxvar;

	srandom(time(0));
	printf("rgb_to_int(\"FFFFFF\") = %d\n", rgb_to_int("FFFFFF"));
	mlx = mlx_init();
	if (!mlx )
	{
		printf(" !! mlx_init fail !!\n");
		exit(1);
	}
	win1 = mlx_new_window(mlx,WINX,WINY,"fdf");
	if (!win1)
		printf("!! mlx_new_window fail !!\n");
	
	myxvar.mlx = mlx;
	myxvar.win = win1;
	myxvar.winsize_x = WINX;
	myxvar.winsize_y = WINY;

	mlx_set_font(mlx, win1, FONT);
	mlx_string_put(mlx,win1, WINX/2-100, 30, 0xFFFFFF,"Fil de Fer");

	// (341, 384) -> (482, 419)
	line.x0 = 341;
	line.y0 = 384;
	line.x1 = 482;
	line.y1 = 419;
	// draw_line(line, WHITE, mlx, win1);
	draw_thick_line(line, WHITE, myxvar);
	mlx_key_hook(win1,key_win1, &myxvar);
	mlx_loop(mlx);
}

// the proof that the rotation matrix is **not** length conserving!!!
// FIXME: remove before submission!!!!
void	mat_mult_test(void)
{
	double a[3][3] = {
		{1.000000,0.000000,0.000000},
		{0.000000,0.995004,0.099833},
		{0.000000,-0.099833,0.995004},
	};
	t_vec v;
	v.x = 0, v.y = 1, v.z = 0;
	for (int i=0;i < 20;i++) {
		mult_mat_vec(a, &v);
		printf("v = (%lf, %lf, %lf)\n", v.x, v.y, v.z);
		printf("len = %lf\n", vec_len(v));
	}
}

