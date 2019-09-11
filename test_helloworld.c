#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
         long int amma = syscall(587);
         printf("System call sys_HelloWorld returned %ld\n", amma);
         return 0;
}
