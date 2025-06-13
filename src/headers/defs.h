#pragma once

#include <stdint.h>

#define SHM_NAME "/xd"

struct config {
	uint32_t width;
	uint32_t height;
	uint32_t pages; 	//just set 1 if not apply
	uint8_t  adrsmode;	
	uint8_t  updateInterval;
};

#define FCONFIG "config"


//I gotta check if there are more, for now this is for SSD1306

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

#define ANSIESC_HOME 		"\033[H"


#define UNIC_BLOCKUP 		"\u2580"
#define UNIC_BLOCKLOW 		"\u2584"
#define UNIC_BLOCKFULL 		"\u2588"
