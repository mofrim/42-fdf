// TODO test this in a ubuntu VM!

#include "mlx.h"
#include "fdf.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>



int key_win1(int key,void *p)
{
	printf("Key in Win1 : %d\n",key);
	if (key == 113)
		exit(0);
	return (0);
}

int main()
{
	void *mlx;
	void *win1;
	int	i;
	int	color;

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
	// mlx_set_font(mlx, win1, "-------24-------");
	mlx_string_put(mlx,win1, 1, 20, 0xFFFFFF,"Fil de Fer");
	mlx_pixel_put(mlx, win1, 100, 100, rgb_to_int(WHITE));
	mlx_key_hook(win1,key_win1,0);
	mlx_loop(mlx);
}


