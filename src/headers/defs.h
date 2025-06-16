#pragma once

#include <stdint.h>
#include <time.h>

#include "../shared.h"

struct binds {
	char keyQ;
	char keyA;
	char keyB;
	char keyC;
	char keyD;
	char keyE;
	char keyF;
	char keyG;
};

struct config {
	uint32_t width;
	uint32_t height;
	uint8_t  adrsmode;	
	struct timespec Updateinterval;
	struct timespec InputInterval;
	struct binds binds;
};

typedef struct {
	uint8_t * keys;
	struct binds * binds;
	struct timespec * inputInterval;
} keyManagerArgs;


#define FCONFIG "config"


//I gotta check if there are more adressing modes, for now this is for SSD1306

#define ADR_H 0
#define ADR_V 1

#define ANSIESC_CUP 		"\033[1A"
#define ANSIESC_CDOWN 		"\033[1B"
#define ANSIESC_CRIGHT		"\033[1C"
#define ANSIESC_CLEFT 		"\033[1D"

#define ANSIESC_CUPX4 		"\033[4A"
#define ANSIESC_CDOWNX4		"\033[4B"
#define ANSIESC_CRIGHTX4	"\033[4C"
#define ANSIESC_CLEFTX4		"\033[4D"

#define ANSIESC_HABSOLUTE	"\033[1G"
#define ANSIESC_VABSOLUTE	"\033[1d"

#define ANSIESC_HOME 		"\033[H"


#define UNIC_BLOCKUP 		"\u2580"
#define UNIC_BLOCKLOW 		"\u2584"
#define UNIC_BLOCKFULL 		"\u2588"

#define BYTE_SIZE 			8

#define MStoNS 				1000000

