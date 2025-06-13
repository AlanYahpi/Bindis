#pragma once

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "defs.h"


static inline int8_t updateTerminal(uint8_t * buffer, struct display display, uint32_t bufferBytes){
	struct winsize wnsize;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &wnsize);

	if (
			wnsize.ws_col < display.width 
			||
			wnsize.ws_row < (display.height/2) 
			){
		return 1;
	}

	printf("\033[2J"); 		//cleans screen
	printf(ANSIESC_HOME);
	
	int xd = 1, tmp = 0;
	int top, bott;
	

	for (uint32_t i = 0; i < bufferBytes; i++){
		
		tmp = buffer[i];
		for (uint8_t a = 0; a < CHAR_BIT; a+=2){

			top  = 	(tmp & 0b01);
			bott = 	(tmp & 0b10);
			tmp >>= 2;

			fflush(stdout);

			//box drawing characters
			if 		(top && bott) 	printf(UNIC_BLOCKFULL 	ANSIESC_CLEFT);
			else if (top && !bott)	printf(UNIC_BLOCKUP 	ANSIESC_CLEFT);
			else if (!top && bott) 	printf(UNIC_BLOCKLOW 	ANSIESC_CLEFT);
			fflush(stdout);
			printf(ANSIESC_CDOWN);
		}
		if ( 
				( (bufferBytes + 1) % display.width ) == 0 
				) printf(ANSIESC_HABSOLUTE); 
		printf(ANSIESC_CRIGHT);
		printf(ANSIESC_CUPX4);
		fflush(stdout);


	}

	return 0;
}

static inline int8_t initTerminal(
		struct termios * newt,
		struct termios * oldt
		){
	printf(
			"\033[?1049h" 		//alternate buffer
//			"\033[?25l" 		//hide cursor
			ANSIESC_HOME
			);
	fflush(stdout);

	//disable echo & canon
	tcgetattr(STDIN_FILENO, oldt);
	*newt = *oldt;
	newt->c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, newt);
	tcflush(STDIN_FILENO, TCIFLUSH);
	
	//disable input blockin
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	if (flags == -1) return 1;
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

	return 0;
}

static inline void finishTerminal(struct termios * oldt){

	printf(
			"\033[?1049l"		//back to normal buffer
			"\033[?25h" 		//show cursor
			);
	fflush(stdout);
	tcsetattr( STDIN_FILENO, TCSANOW, oldt);
	tcflush(STDIN_FILENO, TCIFLUSH);
}
