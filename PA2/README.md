### Mengyu Wu

SID: 107207928

Email: mewu0016@colorado.edu

### Submission Contens: Enter /home/kernel/linux-hwe-4.15.0/modules

1. simple_char_driver.c
  
    Implementation of Device Deriver to handle Device files by Major number and control the physical devices and included
    Read(), Write(), Open(), Close() and llseek().
        
2. Makefile
    
    Adjusting Makefile in order to let simple_char_driver.c are compiled to .o files.
    
3. /dev/simple_character_device

    Implementation of Devicee file to handle sginal from user space and send file-operations to Devie Driver with major number
    
4. simple_char_test.c
  
    Implementation of a interface for user to send file operations and through the device file send to deriver file.
    
## To Run
1. Ensure all files in this submission have been placed in their respective file paths.

2. Compile and Run each test program with commands below

      "sudo make -C /lib/modules/$(uname -r)/build M=$PWD modules" to compile module files
      
      "sudo insmod simple_char_driver.ko" to load the module to kernel
      
      "sudo mknod -m 777 /dev/simple_character_device c 240 0" to create device file in /dev
      
      "sudo gcc simple_char_test.c" to compile the test app
     
3. After test process, enter "dmesg" to check the information print in kernel
      
4. remove the module

    "sudo rmmod simplee_char_driver" to remove the module from kernel
    
    "sudo rm /dev/simple_character_device" to remove device file
