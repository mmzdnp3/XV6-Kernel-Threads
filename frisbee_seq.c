#include "types.h"
#include "stat.h"
#include "user.h"

int numPasses;
int numThreads;
int currPass = 1;
int holder = 0;
lock_t lock;

int sequenceNum = 0;

void passFrisbee(void* arg)
{
	int threadnumber = *(int*)arg;
	for(;;)
	{	
	//	sleep(100);
		int check, skip, break_;	
		do
		{
			check = sequenceNum;
			skip = 0;
			break_ = 0;
			if(numPasses <= 0)
			{
				break_ = 1;
			}
			if(holder != threadnumber)
			{
				skip = 1;
			
			}
			sleep(1);
//			printf(0,"c:%d, s:%d\n", check, sequenceNum);
		}while(check != sequenceNum);
		
		if(break_ == 1)
		{
			break;
		}	
		if(skip == 1)
		{
			continue;		
		}
			
		seqlock_acquire(&lock, &sequenceNum);
		holder++;
		if(holder == numThreads)
		{
			holder = 0;
		}
		printf(0, "Pass number no. %d, Thread %d is passing the token to %d\n", currPass, threadnumber, holder);
		numPasses--;
		currPass++;
		seqlock_release(&lock, &sequenceNum);
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

	lock_init(&lock);
	int i,rc;

	for(i = 0; i < numThreads; i++)
	{
		int * t = malloc(sizeof(*t));
		*t = i; 
	//	printf(0,"t = %d\n", *t);
		rc = thread_create((void*)passFrisbee,(void*)t);
	//	printf(0,"rc = %d\n", rc);
	}
	for(i = 0; i < numThreads; i++)
	{
		wait();
	}	
	exit();	
}

