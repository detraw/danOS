#include "kernel.h"
#include "errors.h"
#include "task.h"
/* Should be removed */
#include "dev.h"

static int next_fd()
{
	int fd;

	for (fd = 0; fd < MAXFILES; fd++) {
		if (current.files[fd].dev_id == DEV_NODEV) {
			return fd;
		}
	}
	return -1;
}

int syscall_open(int dev)
{
	int fd, rc;

	fd = next_fd();
	if (fd < 0) {
		return ERR_N_FILES;
	}

	rc = open_device(dev, &current.files[fd]);
	return rc;
}

int syscall_close(int fd)
{
	if (fd < 0 || fd >= MAXFILES) {
		return ERR_INVALID_FILE;
	}

	if (current.files[fd].dev_id == DEV_NODEV) {
		return ERR_NO_SUCH_FILE;
	}

	if (current.files[fd].ops->close) {
		current.files[fd].ops->close();
	}

	current.files[fd].dev_id = DEV_NODEV;

	return 0;
}

int syscall_write(int fd, const char *s)
{
	if (fd == 0) {
		console_write(s);
	}
#if 0
	if (fd < 0 || fd >= MAXFILES) {
		return ERR_INVALID_FILE;
	}

	if (current.files[fd].ops->write) {
		return current.files[fd].ops->write(s);
	}

	return ERR_NO_SUCH_FILE;
#endif
}
