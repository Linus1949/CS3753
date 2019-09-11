#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        if(argc == 3){
		int ptr;
		long int amma = syscall(589, atoi(argv[1]), atoi(argv[2]), &ptr);
		printf("System call sys_cs3753_add returned %ld\n", amma);
		return 0;
		
	}
	else{
		printf("enter input! \n");
		return -1;
	}
}
