#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "mmu.h"

void seqlock_acquire(lock_t *lock, int*seq)
{	
	while(xchg(&lock->locked,1) !=0); //consulting xv6's spinlock.c
	(*seq)++;
}


void seqlock_release(lock_t *lock, int* seq)
{
	//lock->locked =0;
	asm volatile("movl $0, %0" : "+m" (lock->locked) : );
	(*seq)++;	
}




