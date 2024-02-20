# os161-Kernel-Src-Add-System-Call-Assignment
Base kernel suitable for Assignment on adding system calls

This repository is the `src` folder of `OS/161`. This `src/` is especially designed for this assignment. 
Clone this repository from inside `~/os161` so it exists at the same level of the already existing `src/` directory. 

Once you clone the repository, you will see that it will have a long name, something like `fall2020-assignment-01-os-161-code-reading-<your-github_username>`. For example, github user `brucewayne` would have this repository named `fall2020-assignment-01-os-161-code-reading-brucewayne`. Despite its name, this directory is actually your `src/` for your new OS/161 kernel (the new `src/` you will use for the assignment). 

You don't need to rename the cloned directory to `src`. But, it is fine if you want to change the directory's name to `src/` for some reason (e.g., name is too long!). Here, you will need to rename the previous `src/` directory or simply delete it.  

Follow the instructions to complete the assignment.  

In this assignment, you will implement:

- Two new system calls (i.e., `printchar` and `add_three_integers`). For three these new calls, you will need to implement all the steps needed to add a system call to the OS.

- The user-level programs to test the new system calls. 

### Configure OS/161 for ASST2
Reconfigure your kernel for this assignment:
```shell
% cd kern/conf
% ./config ASST3
You should now see an ASST3 directory in the compile directory.
```

### Syscall: `int printchar(char c)`

This system call should be added as system call number 41 (and ensure the number you choose is not being used by another system call). If this number is being used then just choose another one that is not being used. This system call passes a single character to the operating system and is handled by having the kernel print the character using the internal kprintf function.

Note that the system-call signatures given here are the user-level functions. In other words, they are the functions that user programs will call to invoke these system calls. These functions' kernel-level counterparts are named differently, e.g., in OS/161 the function name has a prefix sys_ (e.g., `sys_reboot` is called to handle the reboot system call).

You will need to modify the code in `kern/arch/mips/syscall.c` to detect your new system calls and dispatch appropriate system call handlers. Although these system calls are simple enough to implement fully within `syscall.c`, it is good programming practice to put the handlers in a separate function in a file in the `kern/syscall` subdirectory. You will also need to add an entry for this new file in the `kern/conf/conf.kern` file, and reconfigure your kernel so that it is included in the build (i.e., if you add new files, you must reconfigure the kernel so the makefiles are updated with the new files to be built). Also, because you want to call functions from `syscall.c` that are defined elsewhere, you should add prototypes for these functions to the `kern/include/syscall.h` header file, similar to what is done for the `sys_reboot` function.

Once you are ready to test, add the user-level function prototype for the system call to `unistd.h`, and add printchartest to the list of SUBDIRS in `userland/testbin/Makefile`, and then recompile the user-level code. If you don’t add the name of the directory of the new test programs, `bmake` will not compile the test programs.

#### Test program: 

```c
#include <unistd.h> 
int main(){

  printchar('C');
  printchar('S');
  printchar('E');   
  printchar('4');
  printchar('0');
  printchar('0'); 
  printchar('1'); 
  printchar('\n'); 

  return 0;
} 
```

### **Syscall**: `int add_three_integers(int a, int b, int c)`

This system call should be added as system call number 43 (and ensure the number you choose is not being used by another system call). If this ID number is being used then just choose another one that is not being used. This system call receives three integers as input and returns their sum (i.e., sum = a + b + c). 

The implementation is similar to that of `printchar()`. However, instead of accepting a single input argument, the function accepts three. Another difference is that the user-level version of `printchar()` does not return a value, i.e., its return value is set to `void`. In contrast, the user-level version of `add_three_numbers()` returns the sum of the three numbers. 

On the system-call handler (i.e., the file `syscall.c` that has the `switch/case` block), the call to the kernel-level implementation must return an integer value that is either 0 (i.e., success) or nonzero (i.e., error code). Given this restriction, the return value of the kernel-level prototype cannot be the sum of the numbers. To be able to acquire the value of the sum from the kernel-level function, you will pass the return variable (i.e., `ret`) as an argument by *reference* to the function. Passing an argument by reference in C-language is done by passing the address of the variable. 

The prototype of the kernel-level function will then be `int sys_add_three_integers(int a, int b, int c, int &ret)`. Note that, in this case, the prototype of the user-level function (i.e., the function that is called by the test program) which is declared as `int add_three_integers(int a, int b, int c)` differs from the kernel-level version by an extra input argument (i.e., the reference to the `ret` variable). This difference is fine as long as the list of argument types are placed in the order matching the arguments of the user-level prototype.

#### Test program:  

```c
 #include <unistd.h> 
int main(){

  int s1 = add_three_integers(3, 5, 2);
  int s2 = add_three_integers(-5, 3, 1);

  return 0;
} 
```

**Important**: You will not be able to use printf to print the result of the sum. In OS/161, `printf()` calls `write()`. However, the `write()` function is not implemented in the current version of the OS/161 that you are using for this assignment. As a result, calling printf() will cause an error (i.e., missing syscall). 

**If you want to see the result of the sum, you can try one of the following approaches:**

1. Create yet another system call with a signature int `sys_printint(int x)` and its user-level counterpart int `printint(int x)`. In this option, you will need to implement all the steps of this new `printint()` system call, except for the test program since you will be testing it from your user-level test program for `sum_three_integers()`. 

2. Simply call `kprintf()` from inside the kernel-level version of `sum_three_integers()`. That should be sufficient for the scope of this assignment. 

 







#### Screenshots of test programs of system calls

Include your screenshots here ... 
