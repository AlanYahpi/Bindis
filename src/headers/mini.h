#pragma once

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

static inline uint8_t closeManager(){
	char c;
	read(STDIN_FILENO, &c, 1);
	if (c == 'q') return 0;
	else return 1;
}

