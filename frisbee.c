#include "types.h"
#include "stat.h"
#include "user.h"

void passFrisbee(void* arg)
{
	printf(0, "whats going on\n");
	exit();
}


int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf(0,"Usage: frisbee numThreads numPasses\n");
		exit();
	}
	int numThreads = atoi(argv[1]);
	int numPasses = atoi(argv[2]);
	printf(0,"Num Threads: %d, Num Passes: %d\n", numThreads, numPasses);
	
	//int rc = thread_create((void*)passFrisbee,0);
	
	//printf(0,"rc = %d\n", rc);
	
	//wait();	
	exit();	
}

