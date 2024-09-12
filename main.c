// TODO test this in a ubuntu VM!

#include "fdf.h"
#include "mlx.h"
#include "mlx_int.h"

// #define FONT "-misc-fixed-*-*-*-*-30-*-*-*-*-*-*-*"
#define FONT "-*-*-*-*-*-*-*-*-*-*-*-*-*-*"


/* Down 65364
 * Up 65362
 */
int key_win1(int key,t_myxvar *p)
{
	static double i;
	static double j;

	i = 0;
	printf("Key in Win1 : %d\n",key);
	if (key == 113)
	{
		mlx_destroy_window(p->mlx, p->win);
		free(p->mlx);
		exit(0);
	}
	if (key == 119)
		mlx_destroy_window(p->mlx, p->win);
	// x
	if (key == 120)
	{
		i = -0.1;
		mlx_clear_window(p->mlx, p->win);
		general_proj(p->map, 0, i, 0);
		draw_all_the_lines(p->map, *p);
		draw_map_fat_points(p->map, "00FF00", *p);
	}
	// s
	if (key == 115)
	{
		i = 0.1;
		mlx_clear_window(p->mlx, p->win);
		general_proj(p->map, 0, i, 0);
		draw_all_the_lines(p->map, *p);
		draw_map_fat_points(p->map, "00FF00", *p);
	}
	// y
	if (key == 121)
	{
		i = -0.2;
		mlx_clear_window(p->mlx, p->win);
		general_proj(p->map, i, 0, 0);
		draw_all_the_lines(p->map, *p);
		draw_map_fat_points(p->map, "00FF00", *p);
	}
	// a
	if (key == 97)
	{
		i = 0.2;
		mlx_clear_window(p->mlx, p->win);
		general_proj(p->map, i, 0, 0);
		draw_all_the_lines(p->map, *p);
		draw_map_fat_points(p->map, "00FF00", *p);
	}
	if (key == 65363)
	{
		j = 10;
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->map, 1, (int)j, 0);
		draw_all_the_lines(p->map, *p);
		draw_map_fat_points(p->map, "00FF00", *p);
	}
	if (key == 65361)
	{
		j = -10;
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->map, 1, (int)j, 0);
		draw_all_the_lines(p->map, *p);
		draw_map_fat_points(p->map, "00FF00", *p);
	}
	// Down key, but up
	if (key == 65364)
	{
		j = 10;
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->map, 1, 0, (int)j);
		draw_all_the_lines(p->map, *p);
		draw_map_fat_points(p->map, "00FF00", *p);
	}
	// Up key, but down
	if (key == 65362)
	{
		j = -10;
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->map, 1, 0, (int)j);
		draw_all_the_lines(p->map, *p);
		draw_map_fat_points(p->map, "00FF00", *p);
	}
	return (0);
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

void	mat_mult_test(void)
{
	double a[3][3] = {
		{1,0,0},
		{0,1,0},
		{0,0,0}
	};
	t_vec v;
	v.x = 3, v.y = 4, v.z = 5;
	mult_mat_vec(a, &v);
	ft_printf("v = (%d, %d, %d)\n", v.x, v.y, v.z);
}

int main(int ac, char **av)
{
	// main1();

	void *mlx;
	void *win1;
	t_map	*map;
	t_myxvar myxvar;

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
	myxvar.mlx = mlx;
	myxvar.win = win1;
	myxvar.winsize_x = WINX;
	myxvar.winsize_y = WINY;

	map = read_map(av[1]);

	myxvar.map = map;
	ft_printf("\n");
	print_map(map);
	ft_printf("\n");

	// isometric_proj(map);
	general_proj(map, 0, M_PI/2 - 0.7, M_PI/2 - 0.7);
	// print_map(map);
	// ft_printf("hey!\n");
	trans_zoom_map(map, 60, myxvar.winsize_x/4, myxvar.winsize_y/2);
	ft_printf("\npre-draw-all-the-lines:\n");
	print_map(map);
	ft_printf("\n");
	draw_all_the_lines(map, myxvar);
	draw_map_fat_points(map, "00FF00", myxvar);
	// ft_printf("map[0,0] = (%d, %d, %d)\n", map[0][0].x, map[0][0].y, map[0][0].z);
	mlx_key_hook(win1,key_win1, &myxvar);
	mlx_loop(mlx);
}


