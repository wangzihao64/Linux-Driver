#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char const* argv[])
{
	int fd=open("/dev/xxx_sample_chardev",O_RDWR);
	if(fd==-1){
		perror("open err");
		return -1;
	}
	int val=10;
	int nbytes=write(fd,&val,sizeof(int));
	if(nbytes==-1){
		perror("write err:\n");
		return -1;
	}
	nbytes=read(fd,&val,sizeof(int));
	if(nbytes==-1){
		perror("read err:\n");
		return -1;
	}
	close(fd);
	return 0;
}
