#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int	main(void)
{
	int i;

	i = 0;
	while (1)
	{
		printf("%d\n", i);
		sleep(1);
		i++;
	}
	return (0);
}
