#include "stm32f4_discovery.h"

#include "syscalls.h"
#include "kernel.h"
#include "file.h"


#if 0
int sleep(int s, int p)
{
	asm volatile ("svc #" SYSCALL_NR_SLEEP_STR);

	return 0;
}
#endif

__attribute__ ((noinline)) int write(int fd, const char *s)
{
	(void)(fd);
	(void)(s);
	register int ret __asm__ ("r0");

	asm volatile ("svc #" SYSCALL_NR_WRITE_STR);
	return ret;
}

__attribute__ ((noinline)) int open(int dev)
{
	(void)(dev);
	register int ret __asm__ ("r0");

	asm volatile ("svc #" SYSCALL_NR_OPEN_STR);
	return ret;
}

void __attribute (( naked )) SVC_Handler(void)
{
	asm volatile ("tst	lr, #4\n\t"
		      "ite	eq\n\t"
		      "mrseq	r0, msp\n\t"
		      "mrsne	r0, psp\n\t"
		      "b	svc_handler_c\n\t"
		      : /* no output */
		      : /* no input */
		      : "r0" /* clobber */);
}

void svc_handler_c(unsigned int *svc_args)
{
	uint8_t svc_number;

	svc_number = ((char *) svc_args[6])[-2]; /* memory[(stacked pc)-2] */

	switch (svc_number) {
	case SYSCALL_NR_OPEN:
		svc_args[0] = syscall_open((int)svc_args[0]);
		break;
	case SYSCALL_NR_WRITE:
		svc_args[0] = syscall_write((int)svc_args[0], (const char *)svc_args[1]);
		break;
	case SYSCALL_NR_SLEEP:
		/* svc_args[0] = syscall_sleep((int)svc_args[0]); */
		break;
	default:
		svc_args[0] = ERR_NO_SYS;
		break;
	};

	return;
}
