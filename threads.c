#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "mmu.h"

//spin lock
void lock_init(lock_t *lock)
{
	lock->locked = 0;
}

void lock_release(lock_t *lock)
{
	asm volatile("movl $0, %0" : "+m" (lock->locked) : );	
	//lock->locked =0;
}

void lock_acquire(lock_t *lock)
{
	while(xchg(&lock->locked,1) !=0); //consulting xv6's spinlock.c
}




int thread_create(void*(*start_routine)(void*), void* arg)
{
	char* stack = malloc(PGSIZE);
	//char* temp = malloc(100);
	//char* temp = stack + PGSIZE+4;
	//*temp = 'a';
	
//	printf(0,"Allocated stack, currently pointing at: %p\n",(void*) stack);
	//printf(0,"temp is currently pointed at: %p\n",(void*) temp);
	//free(temp);	
	if(stack == 0)
	{
		return -1;
	}
/*
	printf(0,"before manipulating stack\n");
	//Store address of argument
	//char* addressArg;
	//Count number of arguments
	int argc =0;
	//Null terminator
	//char null = '\0';
	//pointer for setting up the stack
	char* ptr = stack+PGSIZE;
	//if there are no arguments;
	printf(0,"stack is currently %p\n", stack);
	printf(0,"ptr is currently %p\n", ptr);

	if(arg ==0)
	{
		ptr -=4;
		//printf(0,"Before setting argc\n");
		*ptr = argc;
		ptr -=4;
		//printf(0,"Before setting fake return addess\n");
		*ptr =(int)0xFFFFFFFF; 
	}	
	
	printf(0,"ptr is now %p, esp needs to be set to this\n",ptr);
	
	printf(0,"Before clone\n");
*/
	int id =  clone(stack, PGSIZE);
	
	if(id < 0)
	{
		printf(0,"Something bad happened with clone\n");
		return -1;
	}	
	
	if(id == 0)
	{
	//	printf(0,"This is child thread\n");	
		(start_routine)(arg);

	//	int j;
	//	for(j = 60; j < 120; j++)
	//	{
	//		printf(0,"%d\n", *(stack-j));
	//	}
		
		printf(0,"Freeing stack at address: %p\n",(void*) stack);
		free(stack);
		exit();
	}
	else
	{
	//	printf(0,"This is parent thread, child thread has pid: %d\n", id);
	}

	return id;	
}
