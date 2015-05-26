#ifndef SYSCALL_H_
#define SYSCALL_H_

#define SYSCALL_NR_OPEN 0x01
#define SYSCALL_NR_OPEN_STR "0x01"
#define SYSCALL_NR_WRITE 0x02
#define SYSCALL_NR_WRITE_STR "0x02"
#define SYSCALL_NR_SLEEP 0x03
#define SYSCALL_NR_SLEEP_STR "0x03"

#define SYSCALL_CALL(a) asm volatile ("svc #"#a)

int syscall_sleep(int s, int p);

int write(int fd, const char *s);
int open(int dev);

#endif
