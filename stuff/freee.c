#include <stdlib.h>
#include <stdio.h>

typedef struct s_a {
	char	*moep;
} t_a;

void thisandthat(t_a *p)
{
	free(p->moep);
	free(p);
	p = NULL;
}

int main(void)
{
	t_a *b = malloc(sizeof(t_a));
	b->moep = malloc(10);
	thisandthat(b);
	printf("b = %p\n", b);
}
