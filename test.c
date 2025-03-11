#include "libc.h"
#include <errno.h>

int main()
{

	// access("hej", F_OK);
	char *args[2] = {"/bin/", NULL};
	execve(args, args, 0);
	// printf("%s\n", strerror(errno));
}