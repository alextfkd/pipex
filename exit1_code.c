#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "signal.h"

int	main(int argc, char **argv)
{
	write(STDERR_FILENO, "ERROR MSG: EXIT 1\n", 18);
	printf("exit 1");
	kill(getpid(), SIGTERM);
	printf("exit 1 (after term)");
	return (1);
}