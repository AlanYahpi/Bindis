#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <limits.h>
#include <termios.h>


#include "headers/defs.h"
#include "headers/dataTrans.h"
#include "headers/renderer.h"
#include "headers/mini.h"
#include "headers/config.h"

int main(int agrc, char * argv[]){
	int isError = 0;
	struct config config;
	struct termios newt, oldt;
	struct winsize wnsize;

	isError = configure(&config);
	if (isError) goto end;
	off_t size = config.width * config.height / CHAR_BIT;

	isError = (!isatty(STDOUT_FILENO));
	if (isError) goto end;

	int fd = memshareInit();
	if (fd == -1) goto end;

	isError = ftruncate(fd, size);
	if (isError) goto end;

	isError = initTerminal(&newt, &oldt);
	if (isError) goto end;

	uint8_t * buffer = 
		mmap(
			NULL,
			size,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			fd, 0
			);
	uint8_t xdtest[] = {0xC2, 0xff, 0b11111101};


	while (closeManager()){
		/*
		updateTerminal(
				buffer,
				config,
				size,
				&wnsize
				);
		*/

		//this is for testing, real one is the upper one
		
		isError = updateTerminal(
				xdtest,
				config,
				3,
				&wnsize
				);
		if (isError) goto end;
		sleep(config.updateInterval);
	}



end:
	shm_unlink(SHM_NAME);
	if ( (isError != 2) || (isError != 3) ) finishTerminal(&oldt);

	switch (isError) {
		case 1:
			printf("something failed :(\n");
			break;
		case 2:
			printf("Check your config file\n");
			break;
		case 3:
			printf("Do u have a config file?\n");
			break;
		case 4:
			printf("Not enough space in terminal for your dimentions\n");
			printf("\tTerminal\tConfig\n"
					"Width\t%i\t\t%u\n"
					"Height\t%i\t\t%u\n",
					wnsize.ws_col, config.width,
					wnsize.ws_row*2, config.height
					);
			break;
	
	}
	return isError;
}
