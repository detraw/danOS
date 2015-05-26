#ifndef FILE_H_
#define FILE_H_

struct file_ops {
	void (*open)(void);
	void (*close)(void);
	int (*write)(const char *s);
};

struct file {
	int dev_id;
	struct file_ops *ops;
};

int syscall_open(int dev);
int syscall_close(int fd);
int syscall_write(int fd, const char *s);

#endif
