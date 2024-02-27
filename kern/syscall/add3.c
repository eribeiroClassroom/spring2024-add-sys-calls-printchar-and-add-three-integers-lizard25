#include<types.h>
#include<lib.h>
#include<syscall.h>
int sys_add3(int a, int b, int c, int *ret){
    *ret = a + b + c;
    return 0; 
}

