#include "stm32f4_discovery.h"
#include "printk.h"
#include "task.h"
#include "dump.h"

static void idle(void)
{
	/* Idle forever */
	while(1);
}

/* temp test function */
void *write_test(void *ptr)
{
	write(0, "slugger\n");
	write(0, "%d\n", 10/0);	/* trigger exception */

	while(1);
}

static char green_stack[1024];

/* called last during kernel boot, should setup userland
   and switch away from kernel mode */
void init_start(void)
{
	printk("starting init\n");

	tasks[current_task].flags = IN_USE_FLAG | EXEC_FLAG;

	/* TODO: switch to userland stack and so on here... */

	{
		/* Test dump functions */
		printk("stack=0x%08x\n", green_stack);
		new_task("write_test", write_test, (void *)0, green_stack+sizeof(green_stack), sizeof(green_stack));
	}

	idle();
}
