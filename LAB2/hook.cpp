#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int ret;
	ret = execl (”/bin/vi”, ”vi”,”/Desktop/hooks.txt”, NULL);
	if (ret == -1)
	perror (”execl”);
	return 0;
}

