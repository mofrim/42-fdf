// TODO test this in a ubuntu VM!

#include "fdf.h"

// #define FONT "-misc-fixed-*-*-*-*-30-*-*-*-*-*-*-*"
#define FONT "-*-*-*-*-*-*-*-*-*-*-*-*-*-*"


int key_win1(int key,void *p)
{
	(void)p;
	printf("Key in Win1 : %d\n",key);
	if (key == 113)
		exit(0);
	return (0);
}

void	main1(void)
{
	void *mlx;
	void *win1;
	// int	i;
	// int	color;
	t_line line;

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
	

	mlx_set_font(mlx, win1, FONT);
	mlx_string_put(mlx,win1, WINX/2-100, 30, 0xFFFFFF,"Fil de Fer");

	line.x0 = 50;
	line.y0 = 50;
	line.x1 = 200;
	line.y1 = 200;
	// draw_line(line, WHITE, mlx, win1);
	draw_thick_line(line, WHITE, mlx, win1);
	mlx_key_hook(win1,key_win1,0);
	mlx_loop(mlx);
}

int main(int ac, char **av)
{
	void *mlx;
	void *win1;
	t_map	*map;

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

	map = read_map(av[1]);
	print_map(map);

	// ft_printf("map[0,0] = (%d, %d, %d)\n", map[0][0].x, map[0][0].y, map[0][0].z);

	mlx_key_hook(win1,key_win1,0);
	mlx_loop(mlx);
}


