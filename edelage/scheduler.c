#include "stm32f4xx_rcc.h"

#include "scheduler.h"
#include "task.h"

volatile unsigned int timeslice_ticks;
#define TIMESLICE_MS 10

#if 0
static inline void save_context(void)
{
	asm volatile ("mrs r0, psp\n\t"
		      "stmdb r0!, {r4-r11}\n\t"
		      "msr psp, r0\n\t");
}

static inline void load_context(void)
{
	asm volatile ("mrs r0, psp\n\t"
		      "ldmfd r0!, {r4-r11}\n\t"
		      "msr psp, r0\n\t");
}

static __attribute__ (( always_inline )) inline void *rd_system_sp(void)
{
	void *ptr;
	asm volatile ("mrs %0, msp\n\t"
		      : "=r" (ptr));
	return ptr;
}

static __attribute__ (( always_inline )) inline void wr_system_sp(void *ptr)
{
	asm volatile("msr msp, %0\n\t"
		     :
		     : "r" (ptr));
}

static inline void *rd_thread_sp(void)
{
	void *ptr;
	asm volatile ("mrs %0, psp\n\t"
		      : "=r" (ptr));
	return ptr;
}

static inline void wr_thread_sp(void *ptr)
{
	asm volatile ("msr psp, %0\n\t"
		      :
		      : "r" (ptr));
}
#endif


unsigned long *stack;


void *context_switch(void *sp)
{
	tasks[current_task].sp = sp;
	/* tasks[current_task].sp = rd_system_sp(); */
	current_task++;
	if (current_task == MAX_TASKS) {
		current_task = 0;
	}
	for (; current_task < MAX_TASKS; current_task++) {
		if (tasks[current_task].flags & SLEEP_FLAG) {
			if (tasks[current_task].wake_at <= system_ticks) {
				tasks[current_task].flags &= ~SLEEP_FLAG;
				tasks[current_task].flags |= EXEC_FLAG;
			}
		}
		if (tasks[current_task].flags & EXEC_FLAG) {
			/* TODO: set return type on stack */
			break;
		}
	}
	if (current_task == MAX_TASKS) {
		/* TODO: set return type on stack */
		current_task = 0;
	}
	/* *stack = 0xFFFFFFF9; /\* THREAD_RETURN; *\/ */
	/* wr_system_sp(tasks[current_task].sp); */
	return tasks[current_task].sp;
}

void __attribute (( naked )) PendSV_Handler(void)
{
	asm volatile ("stmdb sp!, {r4-r11}\n\t"
		      "mrs r0, msp\n\t"
		      "bl pendsv_handler_c\n\t"
		      "msr msp, r0\n\t"
		      "ldmfd sp!, {r4-r11}\n\t"
		      "mvns lr, #0x6\n\t"
		      "bx lr\n\t");
}

void SysTick_Handler(void)
{
	system_ticks++;
	timeslice_ticks++;
	if (timeslice_ticks == TIMESLICE_MS) {
		timeslice_ticks = 0;

		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
		/* SCB->ICSR |= (1 << 28);	/\* trigger context switch *\/ */
	}

#if 0
	asm volatile ("stmdb sp!, {r4-r11}\n\t"
		      "mrs r0, msp\n\t"
		      "bl systick_handler_c\n\t"
		      "msr msp, r0\n\t"
		      "ldmfd sp!, {r4-r11}\n\t"
		      "mvns lr, #0x6\n\t"
		      "bx lr\n\t");
#endif

	/* asm volatile ("mrs r0, psp\n\t" */
	/* 	      "stmdb r0!, {r4-r11}\n\t" */
	/* 	      "msr psp, r0\n\t" */
	/* 	      "bl systick_handler_c\n\t" */
	/* 	      "mrs r0, psp\n\t" */
	/* 	      "ldmfd r0!, {r4-r11}\n\t" */
	/* 	      "msr psp, r0\n\t" */
	/* 	      "bx lr\n\t"); */
}

void *pendsv_handler_c(void *sp)
{
	sp = context_switch(sp);

	return sp;
}

int ms_to_ticks(int ms)
{
	/* right now system ticks 1000 times a second */
	return ms;
}

void schedule(void)
{
	SCB->ICSR |= (1 << 28);	/* trigger context switch */
}

void init_scheduler(void)
{
	if (SysTick_Config(SystemCoreClock / 1000)) {
		while(1); 	/* error */
	}
	NVIC_SetPriority(PendSV_IRQn, 0xff);
}
