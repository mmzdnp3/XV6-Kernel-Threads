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
		//printf(0,"Thread %d from the top\n", threadnumber);	
		int check, skip, break_;	

		do
		{
			check = sequenceNum;
			break_ = 0;
			if(numPasses <= 0)
			{
				break_ = 1;
			}
		//	if(check != sequenceNum)
		//	{
		//		printf(0,"c:%d, s:%d\n", check, sequenceNum);
		//	}
		}while(check != sequenceNum);	
		if(break_ == 1)
		{
			break;		
		}
		do
		{
			check = sequenceNum;
			skip = 0;

			if(holder != threadnumber)
			{
				skip = 1;			
			}
		//	if(check != sequenceNum)
		//	{
		//		printf(0,"c:%d, s:%d\n", check, sequenceNum);
		//	}
		}while(check != sequenceNum);
		if(skip == 1)
		{	
			sleep(1);
			continue;
		}	
//		printf(0,"Thread %d trying to acquire, holder is %d\n", threadnumber, holder);
				
		seqlock_acquire(&lock, &sequenceNum);
		
//		printf(0,"thread %d acquired lock\n", threadnumber);
			
		holder++;
		if(holder == numThreads)
		{
			holder = 0;
		}
		printf(0, "Pass number no. %d, Thread %d is passing the token to %d\n", currPass, threadnumber, holder);
		numPasses--;
		currPass++;
		seqlock_release(&lock, &sequenceNum);
		
//		printf(0,"Thread %d released \n",threadnumber);		

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
	
//	sleep(500);
	
//	printf(0,"lock->locked: %d\n", lock.locked);

	for(i = 0; i < numThreads; i++)
	{
		wait();
	}	
	exit();	
}

