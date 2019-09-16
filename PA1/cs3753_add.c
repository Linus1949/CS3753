#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/uaccess.h>

asmlinkage long sys_cs3753_add(int numOne, int numTwo, int *result)
{
	printk(KERN_ALERT "First value is %d\n", numOne); 			//print num_1 in kernel
	printk(KERN_ALERT "Second value is %d\n", numTwo);			//print num_2 in kernel
	*result = numbOne + numTwo;						  			//store result in pointer

	printk(KERN_ALERT "number_1 + number_2 = %d\n", *result);	//print result in kernel

	return 0;
}
