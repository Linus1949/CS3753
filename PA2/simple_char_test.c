#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#define DEVICE "/dev/simple_character_device"
#define BUFFER_SIZE 1024
int debug = 1, fd = 0;
int ppos = 0;



int read_device(){
	int read_size = 0;
	ssize_t ret;
	char *data = (char *)malloc(BUFFER_SIZE * sizeof(char));

	printf("Enter the number of bytes you want to read:\n");
	scanf("%d",&read_size);

	if(debug)
		printf("the number of bytes read is %d\n",read_size);
	memset(data,0,sizeof(data));
	data[0] = '\0';
	ret = read(fd,data,read_size);
	printf("Data read from the device: %s\n", data);
	if(ret == -1)
		printf("reading failed\n");
	else
		printf("reading success\n");
	free(data);
	return 0;
}

int write_device(){
	int write_size = 0;
	ssize_t ret;
	char *data = (char *)malloc(BUFFER_SIZE * sizeof(char));

	printf("Enter data you want to write to the device\n");
	scanf(" %[^\n]",data); /*a space added then it can reads white space" */
	write_size = strlen(data);
	if(debug)
		printf("the length of data written is %d\n", write_size);
	ret = write(fd,data,write_size);
	if(ret == -1)
		printf("written failed\n");
	else
		printf("written success\n");
	free(data);
	return 0;
}

int lseek_device(){
	int offset = 0, whence = 0;
	printf("Enter an offset value: \n");
	scanf("%d",&offset);
	if(debug)
		printf("offset selected is %d\n",offset);
	printf("Enter a value for whence(third parameter)\n");
	scanf("%d",&whence);
	switch(whence){
		case 1: lseek(fd,offset,SEEK_SET);
				return 0;
				break;
		case 2: lseek(fd,offset,SEEK_CUR);
				return 0;
				break;
		case 3: lseek(fd,offset,SEEK_END);
				return 0;
				break;
		default:
			printf("Invaild whence enter, please enter again\n");

	}
	return 0;
}



int main(){
	char choice;

	while(choice!='e'){
		printf("\
				 Press r to read from device\n\
				 Press w to write to the device\n\
				 Press s to seek into the device\n\
				 Press e to exit from the device\n\
				 Press anything else to keep reading or writing from the device\n\n\
				 Enter command:");
		scanf("%s",&choice);
		switch(choice){
			case 'w': printf("Write option selected\n");
					fd = open(DEVICE,O_RDWR);
					write_device();
					break;
			case 'r': printf("Read option selected\n");
					fd = open(DEVICE,O_RDWR);
					read_device();
					break;
			case 's': printf("Read option selected\n");
					fd = open(DEVICE,O_RDWR);
					lseek_device();
					break;
			case 'e': printf("Quite the testapp\n");
					break;
		}
	}
	return 0;
}
