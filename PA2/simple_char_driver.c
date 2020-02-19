#include<linux/init.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
MODULE_AUTHOR("Mengyu WU");
MODULE_LICENSE("GPL");
#define BUFFER_SIZE 1024
#define MY_DEVICE_NAME "my_device"
#define MAJOR_NUMBER 240
/* Define device_buffer and other global data structures you will need here */
int openCounter = 0;
int closeCounter = 0;
char* device_buffer;


ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
	/* length is the length of the userspace buffer*/
	/* offset will be set to current position of the opened file after read*/
	/* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */
	int bytesRead;								/* the number of bytes actually read */
	int bytesToRead;							/* the number of bytes to read */
	int maxBytes = BUFFER_SIZE - *offset; 		/* maximum bytes that can be read from offset to BUFFER_SIZE */
	/* if maximum bytes over the number of space available in user buff */
	if (maxBytes > length){
		bytesToRead = length;
	}
	else{
		bytesToRead = maxBytes;
	}
	if(bytesToRead == 0){
		printk(KERN_ALERT "Reached the end of the device\n");
	}
	bytesRead = bytesToRead - copy_to_user(buffer, device_buffer + *offset, bytesToRead); /* get bytes read by subtract the uncopy bytes (copy_to_user) */
	printk(KERN_ALERT "%d bytes read in the file\n", bytesRead);
	*offset += bytesRead; /* update the current position until reache the end of the file */

	return bytesRead;
}



ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
	/* length is the length of the userspace buffer*/
	/* current position of the opened file*/
	/* copy_from_user function: destination is device_buffer and source is the userspace buffer *buffer */
	int bytesWrite;								/* the number of bytes actually write */
	int bytesToWrite;							/* the number of bytes to write */
	int maxBytes = BUFFER_SIZE - *offset; 		/* maximum bytes that can be read from offset to BUFFER_SIZE */
	/* if maximum bytes over the number of space available in user buff */
	int offsetPos = device_buffer + *offset;
	if(maxBytes > length){
		bytesToWrite = length;
	}
	else{
		offsetPos -= *offset;        /* if buffer remaining space is not enough, we need to back to begin and overwrite */
	}
	bytesWrite = bytesToWrite - copy_from_user(offsetPos, buffer, bytesToWrite); /* get bytes read by subtract the uncopy bytes (copy_from_user) */
	printk(KERN_ALERT "%d bytes written in the file\n", bytesWrite);
	*offset += bytesWrite; /* update the current position until reache the end of the file */

	return bytesWrite;
}


int simple_char_driver_open (struct inode *pinode, struct file *pfile)
{	
    openCounter++;
	/* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
	printk(KERN_ALERT "Opening ->simple_char_driver<- This Driver has been opened %d times until now\n", openCounter);
	return 0;
}

int simple_char_driver_close (struct inode *pinode, struct file *pfile)
{	
	closeCounter++;
	/* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
	printk(KERN_ALERT "Closing ->simple_char_driver<- This Driver has been closed %d times until now\n", closeCounter);
	return 0;
}

loff_t simple_char_driver_seek (struct file *pfile, loff_t offset, int whence)
{
	/* Update open file position according to the values of offset and whence */
	loff_t curr_pos = 0;
	switch(whence)
	{
		/* SEEK_SET */
		case 0: 	
				curr_pos = offset;
				break;
		/* SEEK_CUR  */		
		case 1:
				curr_pos = pfile->f_pos + offset;
				break;
		/* SEEK_END */
		case 2:
				curr_pos = BUFFER_SIZE - offset;
				break;
		/* can't happen */
		default:
				printk(KERN_ALERT "whence error!");
				return -EINVAL; 
	}
	/* seek before the beginning */
	if(curr_pos > BUFFER_SIZE)
		curr_pos = BUFFER_SIZE;
	else if (curr_pos < 0)
		curr_pos = 0;
	pfile->f_pos = curr_pos;

	return curr_pos;
}

struct file_operations simple_char_driver_file_operations = {

	.owner   = THIS_MODULE,
	/* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
	.open 	 = simple_char_driver_open,		/*to open the device*/
	.release   = simple_char_driver_close,	/*to close the device*/
	.llseek	 = simple_char_driver_seek,		
	.read    = simple_char_driver_read,		/*to read the device*/
	.write   = simple_char_driver_write		/*to write the device*/
};

static int simple_char_driver_init(void)
{
	/* print to the log file that the init function is called.*/
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	/* allocate memory for buffer initialization */
	device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	/* register the device */
	register_chrdev(MAJOR_NUMBER,MY_DEVICE_NAME,&simple_char_driver_file_operations);
	return 0;
}

static void simple_char_driver_exit(void)
{
	/* print to the log file that the exit function is called.*/
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	/* free memory before exiting */
	kfree(device_buffer); 
	/* unregister  the device using the register_chrdev() function. */
	unregister_chrdev(MAJOR_NUMBER,MY_DEVICE_NAME);
}

/* add module_init and module_exit to point to the corresponding init and exit function*/
module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);
