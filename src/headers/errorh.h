#pragma once

#include "renderer.h"
#include <unistd.h>
#include <termios.h>
#include <signal.h>
static inline void restauratin(){
	tcsetattr(STDIN_FILENO, TCSANOW, &backup);
}

static inline void handle_sigint(int sig){
	finishTerminal(struct termios *oldt)
	restauratin();
	_exit(1);
}
