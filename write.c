#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void main(int argc,char *argv[])
{
	int fd;
	if(argc<3){
		printf("usage: write device message\n");
		exit(0);
	}
	fd=open(argv[1],O_CREAT | O_WRONLY,S_IRUSR);
    if(fd==-1){
        printf("Error file is not created.\n");
        exit(-1);
    }
    int lenght=strlen(argv[2]);
	write(fd,argv[2],lenght);
    close(fd);
}
