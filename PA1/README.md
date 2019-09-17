### Mengyu Wu

SID: 107207928

Email: mewu0016@colorado.edu

### Submission Contens: Enter /home/kernel/linux-hwe-4.15.0

a. arch/x86/kernel/cs3753_add.c

  Implementation of system call 598 which using KERN_ALERT and printk to print the message of the sum of two numbers.
  
b. arch/x86/kernel/Makefile

  Adjusting Makefile in order to let cs3753_add.c and helloworl.c are compiled to .o files.
  
c. arch/x86/entry/entry/syscalls/syscall_64.tbl

  It is a table of kernel system calls. And note 587(sys_helloworld) and 589(sys_cs3753_add).
  
d. include/linux/syscalls.h

  Header file which contains all declarations of system calls.
  
e. /var/log/syslog

  using dmesg to check the printk message from system call.
  
f. Source code for your test program
  1. test_helloworld.c
  
    tests system call 587 (sys_helloworld). Use dmesg to check printk statement.
    
  2. test_cs3753_add.c
  
    tests system call 589 (sys_cs3753_add). Use dmesg to check printk statement.
    
## To Run:
1. Ensure all files in this submission have been placed in their respective file paths.
2. Compile and Run each test program with commands below
    
    test_helloworld.c
    ./a.out
    test_cs3753_add.c
    ./a.out Number1 Number2
    
3. Check printk logs with comands below

    dmesg
    sudo tail /var/log/syslog
