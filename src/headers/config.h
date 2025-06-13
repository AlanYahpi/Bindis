#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "defs.h"

static inline int8_t configure(
		struct config * config
		){
	config->width          = 0;
	config->height         = 0;
	config->updateInterval = 1;
	config->adrsmode       = ADR_H;


	FILE * fconfig = fopen(FCONFIG, "r");
	if (fconfig == NULL) return 3;

	char  		stringBuffer[32];
	uint32_t 	intBuffer;
	char 		line[255];

	while (fgets(line, sizeof(line), fconfig) != NULL){
		sscanf( line,
				" %s %c %u",
				stringBuffer,
				NULL,
				&intBuffer
				);

		if  	(strcmp(stringBuffer, "width"))				config->width = intBuffer;
		else if (strcmp(stringBuffer, "height"))		  	config->height = intBuffer;
		else if (strcmp(stringBuffer, "pages"))  			config->pages = intBuffer;
		else if (strcmp(stringBuffer, "updateInterval"))  	config->updateInterval = intBuffer;
		else if (strcmp(stringBuffer, "adressingMode"))  	config->adrsmode = intBuffer;

	}
	if (config->height == 0 || config->width == 0) return 2;



	return 0;
}
