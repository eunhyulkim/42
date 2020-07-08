#include <stdio.h>
#include <unistd.h>

int main(void)
{
	sleep(3);
	dprintf(2, "task 1\n");
	return (0);
}

