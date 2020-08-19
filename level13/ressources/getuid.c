#include <unistd.h>

uid_t	getuid(void)
{
	write(2, "getuid\n", 7);
	return 0x1092;
}

uid_t	geteuid(void)
{
	write(2, "geteuid\n", 8);
	return 0x1092;
}

uid_t	getgid(void)
{
	write(2, "getgid\n", 7);
	return 0x1092;
}

uid_t	getegid(void)
{
	write(2, "getegid\n", 8);
	return 0x1092;
}
