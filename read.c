#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc,char *argv[])
{
	int fd;
	char buffer[1024];
	int offset=0;
	
	if(argc<3){
		printf("usage: read device lenght offset\n");
		exit(0);
	}
	int lenght=atoi(argv[2]);
	if(argc==4){
		offset=atoi(argv[3]);
	}
	fd=open(argv[1],O_RDONLY,S_IRUSR);
    if(fd==-1){
        printf("Error file not found.\n");
        exit(-1);
    }
    //read the device with offset as lenght
 	if(offset!=0){
 		read(fd,buffer,offset);
 	} 
 	//read the device with the specific lenght  
    read(fd,buffer,lenght);
	printf("%s",buffer);
    close(fd);
}