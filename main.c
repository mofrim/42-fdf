// TODO test this in a ubuntu VM!

#include "fdf.h"
#include "mlx_int.h"

// #define FONT "-misc-fixed-*-*-*-*-30-*-*-*-*-*-*-*"
// #define FONT "-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
#define FONT "-misc-fixed-bold-r-normal--18-120-100-100-c-90-iso8859-1"
// #define FONT "-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso8859-1"


void	mat_mult_test(void);
void	proj_problem(t_myxvar *mxv);

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
	mxv->auto_center_map = 1;
	mxv->menu_visible = 0;
	mxv->show_markers = 0;
	mxv->orig_map = read_map(av[1]);
	initial_resize_map(mxv, 0, 0);
	mxv->orig_map->alpha = 0;
	mxv->orig_map->beta = 0;
	mxv->orig_map->gamma = 0;
	mxv->orig_map->y_offset = 0;
	mxv->orig_map->x_offset = 0;
	mxv->orig_map->zoom = 1;
	mxv->cur_map = duplicate_map(mxv->orig_map);
	center_map(mxv);

	mlx_set_font(mlx, win1, FONT);

	// DEBUG
	ft_printf("\n");
	print_map(mxv->cur_map);
	ft_printf("\n");

	// draw_all_the_lines(mxv->cur_map, *mxv);

	// proj_problem(mxv);

	// DEBUG
	// ft_printf("zoom, xoff, yoff = %d, %d, %d\n", mxv->cur_map->zoom, mxv->cur_map->x_offset, mxv->cur_map->y_offset);

	// t_pxl p = {p.x = 568, p.y = 324};
	// draw_disk(p, 100, WHITE, *mxv);


	// DEBUG line drawing test
	//
	t_line line;
	line.x0 = 5;
	line.y0 = 15;
	line.x1 = 105;
	line.y1 = 105;
	draw_line2(line, WHITE, *mxv);

	// DEBUG disk drawing test
	//
	// t_pxl p = { p.x = 512, p.y = 384};
	// draw_disk(p, 10, WHITE, *mxv);


	mlx_key_hook(win1, key_win1, mxv);
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

// FIXME remove before sub
void	proj_problem(t_myxvar *mxv)
{
	double rot_z[3][3];
	t_vec v;
	double angl = -M_PI/4;
	t_line line;


	rot_z[0][0] = cos(angl);
	rot_z[0][1] = sin(angl);
	rot_z[0][2] = 0;
	rot_z[1][0] = -sin(angl);
	rot_z[1][1] = cos(angl);
	rot_z[1][2] = 0;
	rot_z[2][0] = 0;
	rot_z[2][1] = 0;
	rot_z[2][2] = 1;

	v.x = 100, v.y = 0, v.z = 0;
	line.x0 = 0;
	line.y0 = 0;
	line.x1 = v.x;
	line.y1 = v.y;
	printf("v = (%lf, %lf, %lf)\n", v.x, v.y, v.z);
	printf("len = %lf\n", vec_len(v));
	draw_thick_line(line, "ff0000", *mxv);
	mult_mat_vec(rot_z, &v);
	line.x0 = 0;
	line.y0 = 0;
	line.x1 = v.x;
	line.y1 = v.y;
	draw_thick_line(line, "ff0000", *mxv);
	printf("v = (%lf, %lf, %lf)\n", v.x, v.y, v.z);
	printf("len = %lf\n", vec_len(v));
	print_mat(rot_z);

}
