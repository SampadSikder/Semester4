#include<stdio.h>
#include<unistd.h>

int main(){
	int pid;
	printf("Unforked\n");
	//printf("I'm the original process with PID %d and PPID %d\n",getpid(), getppid());
	
	pid=fork();
	if(pid!=0){//pid non zero hole parent
		printf("I'm the original process with PID %d and PPID %d\n",getpid(), getppid());
		printf("My childs PID is %d\n", pid);
	}
	else{//pid 0 mane child
		printf("I'm the child process with PID %d and PPID %d\n",getpid(), getppid());
	}
	printf("PID terminates %d\n", getpid());
}
		
	
