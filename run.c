#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include <fcntl.h>
#include<pwd.h>
#include<sys/stat.h>
int main()
{
	int id=fork();
	if(!id)
	{
		execl("./shell","./shell",(char*)NULL);
	}
	int status;
	wait(&status);
	exit(0);
}