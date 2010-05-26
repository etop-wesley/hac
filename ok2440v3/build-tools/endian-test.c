#include <stdio.h>

int main(int argc, char **argv)
{
	union { long l; char c[sizeof (long)]; } u;
	u.l = 1;
	if (u.c[sizeof (long) - 1] == 1)
		printf("big endian\n");
	else
		printf("little endian\n");
	return 0;
}
