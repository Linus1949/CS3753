#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/uaccess.h>

asmlinkage long sys_cs3753_add(int numOne, int numTwo, int *result)
{
	printk(KERN_ALERT "First value is %d\n", numOne);
	printk(KERN_ALERT "Second value is %d\n", numTwo);
	*result = numbOne + numTwo;

	printk(KERN_ALERT "number_1 + number_2 = %d\n", *result);

	return 0;
}
