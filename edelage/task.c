#include "stm32f4xx.h"

#include "task.h"
#include "scheduler.h"
#include "printk.h"

struct hw_stack_frame {
	long r0;
	long r1;
	long r2;
	long r3;
	long r12;
	long lr;
	long pc;
	long psr;
};

struct sw_stack_frame {
	long r4;
	long r5;
	long r6;
	long r7;
	long r8;
	long r9;
	long r10;
	long r11;
};

static void del_task(void)
{
	printk("deleting task '%s'\n", tasks[current_task].name);

	tasks[current_task].flags = 0;
	SCB->ICSR |= (1 << 28);	/* trigger context switch */
	while(1);		/* after context switch this task will be terminated  */
}

int new_task(char *name, void *(*p)(void *), void *arg, void *sp, int stack_size)
{
	int i, pid = 0;
	struct hw_stack_frame *proc_frame;

	for (i = 0; i < MAX_TASKS; i++) {
		if (tasks[i].flags == 0) {
			int j;
			for (j = 0; name[j] != '\0' && j < MAXNAME; j++) {
				tasks[i].name[j] = name[j];
			}

			proc_frame = (struct hw_stack_frame *)(sp - sizeof(struct hw_stack_frame));
			proc_frame->r0 = (long)arg;
			proc_frame->r1 = 0;
			proc_frame->r2 = 0;
			proc_frame->r3 = 0;
			proc_frame->r12 = 0;
			proc_frame->lr = (long)del_task;
			proc_frame->pc = (long)p;
			proc_frame->psr = 0x21000000; /* default psr value */
			tasks[i].flags = IN_USE_FLAG | EXEC_FLAG;
			/* tasks[i].sp = sp + stack_size - sizeof(struct hw_stack_frame) - sizeof(struct sw_stack_frame); */
			tasks[i].sp = sp - sizeof(struct hw_stack_frame) - sizeof(struct sw_stack_frame);
			tasks[i].wake_at = 0;

			pid = i;
			break;
		}
	}
	return pid;
}

void sleep(int ms)
{
	current.wake_at = system_ticks + ms_to_ticks(ms);
	current.flags &= ~EXEC_FLAG;
	current.flags |= SLEEP_FLAG;
	schedule();

#if 0
	unsigned int tick = system_ticks + ms;
	while (system_ticks < tick);
#endif
}
