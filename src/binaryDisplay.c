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
				size
				);
		*/

		//this is for testing, real one is the upper one
		if (
		updateTerminal(
				xdtest,
				config,
				3
				)
		!= 0) goto end;
		sleep(config.updateInterval);
	}



end:
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
	
	}
	shm_unlink(SHM_NAME);
	finishTerminal(&oldt);
	return isError;
}
