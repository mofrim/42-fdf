// TODO test this in a ubuntu VM!

#include "mlx.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void *mlx;
void *win1;

int main()
{
  srandom(time(0));
  mlx = mlx_init();
  win1 = mlx_new_window(mlx,300,300,"win1");
  if (!win1)
	  printf("NULL!\n");
  mlx_loop(mlx);
}
