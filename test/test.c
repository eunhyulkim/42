#include <stdio.h>
#include <unistd.h>

int main(void)
{
	sleep(2);
	dprintf(2, "task 1\n");
	return (0);
}

