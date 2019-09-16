#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        if(argc == 3){//input needs ./a.out num_1 num_2
		int ptr;
		long int amma = syscall(589, atoi(argv[1]), atoi(argv[2]), &ptr);//make a system call #589
		printf("System call sys_cs3753_add returned %ld\n", amma);//return 0 if success
		return 0;
		
	}
	else{
		printf("enter input! \n");//input missing
		return -1;
	}
}
