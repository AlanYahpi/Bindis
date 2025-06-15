#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "defs.h"

static inline int8_t configure(
		struct config * config
		){
	config->width            = 0;
	config->height           = 0;
	config->Updateinterval.tv_nsec = 1 * MStoNS;
	config->Updateinterval.tv_sec = 0;
	config->InputInterval.tv_nsec = (1/60 * 1000) * MStoNS;
	config->InputInterval.tv_sec = 0;
	config->adrsmode         = ADR_H;

	config->binds.keyQ = 'q';
	config->binds.keyA = 'z';
	config->binds.keyB = 'x';
	config->binds.keyC = 'c';
	config->binds.keyD = 'v';
	config->binds.keyE = 'b';
	config->binds.keyF = 'n';
	config->binds.keyG = 'm';


	FILE * fconfig = fopen(FCONFIG, "r");
	if (fconfig == NULL) return 3;

	char  		stringBuffer[32];
	uint32_t 	intBuffer;
	char 		line[255];

	while (fgets(line, sizeof(line), fconfig) != NULL){
		sscanf( line,
				"%s %*c %3u",
				stringBuffer,
				&intBuffer
				);
		if (stringBuffer[0] != '#'){
			if  	(!strcmp(stringBuffer, "width"))			config->width = intBuffer;
			else if (!strcmp(stringBuffer, "height"))		  	config->height = intBuffer;
			else if (!strcmp(stringBuffer, "updateInterval"))  	config->Updateinterval.tv_nsec = intBuffer * MStoNS;
			else if (!strcmp(stringBuffer, "adressingMode"))  	config->adrsmode = intBuffer;
			else if (!strcmp(stringBuffer, "inputInterval"))  	config->InputInterval.tv_nsec = intBuffer * MStoNS;
			else if (!strcmp(stringBuffer, "GPKEY")){
				if 			(!strcmp(stringBuffer + 5+1, "A")) 			config->binds.keyA = (char) intBuffer;
				else if 	(!strcmp(stringBuffer + 5+1, "B")) 			config->binds.keyB = (char) intBuffer;
				else if 	(!strcmp(stringBuffer + 5+1, "C")) 			config->binds.keyC = (char) intBuffer;
				else if 	(!strcmp(stringBuffer + 5+1, "D")) 			config->binds.keyD = (char) intBuffer;
				else if 	(!strcmp(stringBuffer + 5+1, "E")) 			config->binds.keyE = (char) intBuffer;
				else if 	(!strcmp(stringBuffer + 5+1, "F")) 			config->binds.keyF = (char) intBuffer;
				else if 	(!strcmp(stringBuffer + 5+1, "G")) 			config->binds.keyG = (char) intBuffer;
				else if 	(!strcmp(stringBuffer + 5+1, "Q")) 			config->binds.keyQ = (char) intBuffer;
			}
		}


	}
	if (config->height == 0 || config->width == 0) return 2;



	return 0;
}
