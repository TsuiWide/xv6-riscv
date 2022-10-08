#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
/*
 * Write a program that uses UNIX system calls to ''ping-pong'' a byte between
 * two processes over a pair of pipes, one for each direction. The parent should
 * send a byte to the child; the child should print "<pid>: received ping",
 * where <pid> is its process ID, write the byte on the pipe to the parent, and
 * exit; the parent should read the byte from the child, print "<pid>: received
 * pong", and exit. Your solution should be in the file user/pingpong.c.
 */

/*
 * parent ping[1] write--->read ping[0] child
 *        pong[0] read<---write pong[1]
 */

#define BUF_SIZE 16
int
main(int argc, char *argv[])
{
	int ping[2];
	int pong[2];
	char buf[BUF_SIZE];

	// creates a new pipe and records the read and write fd in the array ping/pong.
	pipe(ping);
	pipe(pong);

	if(fork() == 0) {
		// child
		read(ping[0], buf, 4);
		printf("child <%d>: received %s\n", getpid(), buf);
		write(pong[1], "pong", strlen("pong"));

		exit(0);
	} else {
		// parent
		write(ping[1], "ping", strlen("ping"));
		read(pong[0], buf, 4);
		printf("parent <%d>: received %s\n", getpid(), buf);
	}
	
	exit(0);
}
