#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	sig_handler(int signo)
{
	printf("I receive %d\n", signo);
}

int	main(void)
{
	int i;

	i = 0;
	signal(SIGINT, (void *)sig_handler);
	while (1)
	{
		printf("%d\n", i);
		sleep(1);
		i++;
	}
	return (0);
}
