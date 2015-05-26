#ifndef DEV_H_
#define DEV_H_

#include "kernel.h"
#include "file.h"

int open_device(int id, struct file *file);
int register_device(int id, const char *name, struct file_ops *ops);
void unregister_device(int id);

/* TODO: find a better way so the devices doesn't have to be hard coded */
enum device_types {
	DEV_NODEV = 0,
	DEV_USART1 = 1,
};

struct device {
	char name[NAMESIZE];
};


#endif
