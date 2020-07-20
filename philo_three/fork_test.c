#include "philo_three.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		while (1)
			;
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
	return (0);
}
