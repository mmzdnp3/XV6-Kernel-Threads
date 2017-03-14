struct stat;
struct rtcdate;

//cs202
#define MAX_THREADS 200
typedef struct
{
	uint locked;
}lock_t;

typedef struct
{
	int n;			//num of threads
	int queuelast;
	int flags[MAX_THREADS];
}arraylock_t;
//cs202

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int clone(void*, int); //cs202

// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int thread_create(void*(void*),void *arg);	//cs202
void lock_init(lock_t *);	//cs202
void lock_release(lock_t *);	//cs202
void lock_acquire(lock_t *);	//cs202
void arraylock_init(arraylock_t *, int);		//cs202
void arraylock_acquire(arraylock_t *, int*);	//cs202
void arraylock_release(arraylock_t *, int*);	//cs202
void seqlock_acquire(lock_t *, int*);		//cs202
void seqlock_release(lock_t *, int*);		//cs202

