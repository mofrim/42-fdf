
main: main.c
	cc -o main -L. main.c -lmlx -lXext -lX11

win: win.c
	cc -o win -L. win.c -lmlx -lXext -lX11
