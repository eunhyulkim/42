#include <stdio.h>
#include <unistd.h>

int main(void)
{
	sleep(1);
	dprintf(2, "task 2\n");
	return (0);
}

