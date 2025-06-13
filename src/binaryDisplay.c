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

int main(int agrc, char * argv[]){
	int isError = 0;

	if (!isatty(STDOUT_FILENO)) goto end;

	int fd = memshareInit();
	if (fd == -1) return 1;

	struct display display;
	display.width    = 128;
	display.height   = 64;
	display.adrsmode = ADR_H;
	display.pages    = 8;

	off_t size = display.width * display.height / CHAR_BIT;
	isError = ftruncate(fd, size);
	if (isError) goto end;

	uint8_t * buffer = 
		mmap(
			NULL,
			size,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			fd, 0
			);
	uint8_t xdtest[] = {0xC2, 0xff};

	struct termios newt, oldt;

	isError = initTerminal(&newt, &oldt);


	while (closeManager()){
		/*
		updateTerminal(
				buffer,
				display,
				size
				);
		*/

		if (
		updateTerminal(
				xdtest,
				display,
				2
				)
		!= 0) goto end;
		sleep(1);
	}



end:
	shm_unlink(SHM_NAME);
	finishTerminal(&oldt);
	return isError;
}
