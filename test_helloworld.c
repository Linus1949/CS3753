#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
         long int amma = syscall(587);//make a system call #587
         printf("System call sys_HelloWorld returned %ld\n", amma)//If success return 0
         return 0;
}
