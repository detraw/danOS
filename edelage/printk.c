#include <stdarg.h>

#include <usart.h>

static char buf[1024];
static unsigned int pos = 0;

static int fmt_number(char *buf, int len, int num, int base, char pad, int minnum)
{
	char *digits = "0123456789abcdef";
	char tmp[16];		/* 11 needed for digits */
	int pos = 0;
	int rem, n, d;
	/* rem = d - (((int)(d / 10)) * 10); */
	d = num;
	do {
		rem = d % base;
		d /= base;
		tmp[pos] = digits[rem];
		/* tmp[pos] = rem + '0'; */
		/* if (d != 0) { */
			pos++;
		/* } */
	} while (d != 0);


	if (num < 0) {
		tmp[pos++] = '-';
	}

	for (n = pos; n < minnum; n++) {
		tmp[pos] = pad;
		if (n+1 < minnum) {
			pos++;
		}
	}

	n = 0;
	pos--;
	while (pos >= 0 && n < len) {
		buf[n++] = tmp[pos--];
	}
	return n;
}

int isdigit(char c)
{
	if (c >= '0' && c <= '9') {
		return 1;
	}
	return 0;
}

void vprintk(const char *fmt, va_list ap)
{
	int d, minnum = 0;
	char c, *s, pad = ' ';

	while (*(fmt++) && pos < sizeof(buf)-1) {
		if (*(fmt-1) == '\n') {
			buf[pos++] = '\r';
		}
		if (*(fmt-1) != '%') {
			buf[pos++] = *(fmt-1);
			continue;
		}

		if (isdigit(*fmt)) {
			if (*fmt == '0') {
				pad = '0';
				fmt++;
			}
			if (isdigit(*fmt)) {
				minnum = *fmt - '0';
				fmt++;
			}
		}

		switch (*fmt) {
		case 's':
			s = va_arg(ap, char *);
			while (*s && pos < sizeof(buf)) {
				buf[pos++] = *s;
				s++;
			}
			break;
		case 'c':
			c = (char)va_arg(ap, int);
			buf[pos++] = c;
			break;
		case 'd':
			d = va_arg(ap, int);
			pos += fmt_number(buf+pos, sizeof(buf)-pos, d, 10, pad, minnum);
			break;
		case 'x':
			d = va_arg(ap, int);
			pos += fmt_number(buf+pos, sizeof(buf)-pos, d, 16, pad, minnum);
			break;
		};
		fmt++;
	}

	buf[pos++] = '\0';
	usart_write(buf);
	pos = 0;
}

void printk(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vprintk(fmt, ap);
	va_end(ap);
}

void init_printk(void)
{

}
