#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
	
int
main(int argc, char *argv[])
{
  int i;
  if(argc != 2){
		printf("sleep command need pass an argument\n");
		exit(0);
  }

	i = atoi(argv[1]);
	printf("sleep:%d seconds\n", i);
	
	sleep(i);

	exit(0);
}
