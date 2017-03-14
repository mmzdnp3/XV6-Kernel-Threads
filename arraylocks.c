#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "mmu.h"

void arraylock_init(arraylock_t *lock, int numThreads)
{
	lock->n = numThreads;
	lock->queuelast =0;
	int i;
	for(i = 0; i < MAX_THREADS;i++)
	{
		lock->flags[i] = 0;
	}
	lock->flags[0] = 1;
}

void arraylock_acquire(arraylock_t *lock, int *my_place)
{
	*my_place = fetch_and_add(&(lock->queuelast), 1);//check x86.h
	while(!(lock->flags[*my_place % lock->n]))
	{
		sleep(1);
		asm("nop");
	}
	
	
}

void arraylock_release(arraylock_t *lock, int *my_place)
{

	asm volatile("movl $0, %0" : "+m" (lock->flags[*my_place%lock->n]) : );
	asm volatile("movl $1, %0" : "+m" (lock->flags[(*my_place+1)%lock->n]) : );
	/*int i;
	printf(0,"\n\n\n\n\n");
	for(i = 0; i < 100; i++)
	{
		printf(0,"%d",lock->flags[i]);
	}
	printf(0,"\n\n\n\n\n");	*/
}

