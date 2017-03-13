#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "mmu.h"

int thread_create(void*(*start_routine)(void*), void* arg)
{
	char* stack = malloc(PGSIZE*2);
	if(stack == 0)
	{
		return -1;
	}
	// Aligning stack on a 4096 boundary
	if((int) stack % PGSIZE > 0)
	{
		stack = stack + (PGSIZE - (int)stack % PGSIZE); 	
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
		*ptr = null;
		ptr -=4;
		printf(0,"Before setting argc\n");
		*ptr = argc;
		ptr -=4;
		printf(0,"Before setting fake return addess\n");
		*ptr =(int)0xFFFFFFFF; 
	}	
	
	printf(0,"Before clone\n");
*/	
	int id = clone(stack, PGSIZE);
	
	if(id < 0)
	{
		printf(0,"Something bad happened with clone\n");
		return -1;
	}	
	
	if(id == 0)
	{
		printf(0,"This is child thread\n");	
		//(start_routine)(arg);
		//free(stack);
		exit();
	}
	else
	{
		printf(0,"This is parent thread, child thread has pid: %d\n", id);
	}

	return id;	
}
