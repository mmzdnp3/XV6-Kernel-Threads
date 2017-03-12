#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "mmu.h"

int thread_create(void*(*start_routine)(void*), void* arg)
{
	void* stack = malloc(PGSIZE);

	if(stack == 0)
	{
		return -1;
	}

	
	int id = clone(stack, PGSIZE);
	
	if(id < 0)
	{
		printf(0,"Something bad happened with clone\n");
		return -1;
	}	
	
	if(id == 0)
	{
		printf(0,"This is child thread with pid");	
		(start_routine)(arg);
		free(stack);
		exit();
	}
	else
	{
		printf(0,"This is parent thread, child thread has pid: %d\n", id);
	}

	return id;	
}
