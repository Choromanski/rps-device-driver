#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

int fd;

// Define signal handlers here.
void signal_handler(int sig){
	if(sig == SIGRTMIN){
		write(fd, "0\n", 2);
	}else if(sig == SIGRTMIN+1){
		write(fd, "1\n", 2);
	}else if(sig == SIGRTMIN+2){
		write(fd, "2\n", 2);
	}else if(sig == SIGRTMIN+3){
		write(fd, "3\n", 2);
	}else if(sig == SIGTERM){
		close(fd);
		exit(0);
	}else{
		printf("Unknown signal");
	}
}



int main()
{	
	fd = open("/dev/rps", O_WRONLY);
	// Register signal handlers here.
	signal(SIGRTMIN, signal_handler);
	signal(SIGRTMIN+1, signal_handler);
	signal(SIGRTMIN+2, signal_handler);
	signal(SIGRTMIN+3, signal_handler);
	signal(SIGTERM, signal_handler);

 	while(1) pause();
  	return 0;
}
