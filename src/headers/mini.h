#pragma once

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include "defs.h"

static inline uint8_t closeManager(uint8_t * keys, struct binds binds){
	if (*keys & KEY_Q) return 0;
	else {
		char c;
		read(STDIN_FILENO, &c, 1);
		if (c == binds.keyQ) {
			*keys |= KEY_Q; 
			return 0;
		}		
		return 1;
	}
}

static inline void * keysManager(
				void * arguments
				){
	keyManagerArgs * args = (keyManagerArgs *) arguments;

	char c;
	while (!(*args->keys & KEY_Q)){
		read(STDIN_FILENO, &c, 1);
	//	c = 'q';
		*args->keys = 0;

		if 		(c == args->binds->keyQ) *args->keys |= KEY_Q;
		else if (c == args->binds->keyA) *args->keys |= KEY_A;
		else if (c == args->binds->keyB) *args->keys |= KEY_B;
		else if (c == args->binds->keyC) *args->keys |= KEY_C;
		else if (c == args->binds->keyD) *args->keys |= KEY_D;
		else if (c == args->binds->keyF) *args->keys |= KEY_F;
		else if (c == args->binds->keyG) *args->keys |= KEY_G;
		else if (c == args->binds->keyH) *args->keys |= KEY_H;
		nanosleep(args->inputInterval, NULL);
	}
	return NULL;
}
