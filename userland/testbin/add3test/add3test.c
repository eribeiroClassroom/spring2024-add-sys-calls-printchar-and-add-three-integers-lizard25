#include <unistd.h> 
int main(){
	int result = add3(2, 4, 5);
	result = result + 1;
	//did this to get rid of warning
	return 0*result;
}
