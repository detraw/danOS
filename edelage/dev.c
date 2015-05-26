#include "dev.h"
#include "file.h"

static struct file_ops *dev_ops[16];

int open_device(int id, struct file *file)
{
	if (id < 0 || id >= 16) {
		return ERR_NO_DEVICE;
	}

	file->dev_id = id;
	file->ops = dev_ops[id];

	if (file->ops->open) {
		file->ops->open();
	}

	return 0;
}

int register_device(int id, const char *name, struct file_ops *ops)
{
	if (id < 0 || id >= 16) {
		return ERR_NO_DEVICE;
	}

	dev_ops[id] = ops;
	return 0;

#if 0
	struct file *file;

	file = add_file(name, ops);
	if (!file) {
		return ERR_EXISTS;
	}

	return 0;
#endif
}

void unregister_device(int id)
{
	if (id < 0 || id >= 16) {
		return;
	}

	dev_ops[id] = NULL;

#if 0
	struct device *device;

	device = lookup_device(id);
	if (!device) {
		return;
	}

	del_file(device->name);
#endif
}
