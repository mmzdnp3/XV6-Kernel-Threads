#include "types.h"
#include "stat.h"
#include "user.h"


int numPasses;
int numThreads;
int currPass = 1;
int holder = 0;

arraylock_t lock;

void passFrisbee(void* arg)
{
	int threadnumber = *(int*)arg;
	int my_place;
	for(;;)
	{	
		//sleep(100);
		//printf(0,"\n\nThread %d acquiring lock\n\n", threadnumber);
		arraylock_acquire(&lock, &my_place);
		if(numPasses <= 0)
		{
			arraylock_release(&lock, &my_place);
			break;
		}
		if(holder != threadnumber)
		{
			arraylock_release(&lock, &my_place);
			continue;
		}
		
		holder++;
		if(holder == numThreads)
		{
			holder = 0;
		}
		printf(0, "Pass number no. %d, Thread %d is passing the token to %d\n", currPass, threadnumber, holder);
		numPasses--;
		currPass++;
		arraylock_release(&lock, &my_place);
	}
	return;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf(0,"Usage: frisbee numThreads numPasses\n");
		exit();
	}
	numThreads = atoi(argv[1]);
	numPasses = atoi(argv[2]);
	printf(0,"Num Threads: %d, Num Passes: %d\n", numThreads, numPasses);

	arraylock_init(&lock, numThreads);
	
	int i,rc;

	for(i = 0; i < numThreads; i++)
	{
		int * t = malloc(sizeof(*t));
		*t = i; 
		rc = thread_create((void*)passFrisbee,(void*)t);
	}
	for(i = 0; i < numThreads; i++)
	{
		wait();
	}	
	exit();	
}

