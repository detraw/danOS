#ifndef TASK_H_
#define TASK_H_

#include "file.h"

#define current tasks[current_task]

int current_task;

#define IN_USE_FLAG (1 << 0)
#define EXEC_FLAG (1 << 1)
#define SLEEP_FLAG (1 << 2)

#define MAXFILES 8
#define MAXNAME 16

struct task {
	char name[MAXNAME];
	void *sp;
	int flags;
	unsigned int wake_at;

	struct file files[MAXFILES];
};

#define MAX_TASKS 8
struct task tasks[MAX_TASKS];

int new_task(char *name, void *(*p)(void *), void *arg, void *sp, int stack_size);
void sleep(int ms);

#endif
