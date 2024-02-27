#include <types.h>
#include <kern/errno.h>
#include <kern/fcntl.h>
#include <lib.h>
#include <proc.h>
#include <current.h>
#include <addrspace.h>
#include <vm.h>
#include <vfs.h>
#include <syscall.h>
#include <test.h>
/* I added all includes just because it wasnt working
 * and i figured more couldnt break it lolol */
int sys_printchar(char c){
	kprintf("%c", c);
	return 0;
}
