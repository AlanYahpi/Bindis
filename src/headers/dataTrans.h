#pragma once


#include "defs.h"

#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
//shared memory

static inline int memshareInit(){

start:
	int fileDesc = shm_open(
			SHM_NAME,
			O_CREAT | O_EXCL | O_RDWR,
			S_IRWXO);

	if (fileDesc == -1){
		if (errno == EEXIST){
			shm_unlink(SHM_NAME); 
			goto start;
		}
		else return -1;
	} 

	return fileDesc;
}

static inline int8_t finish(){
	shm_unlink(SHM_NAME);
	
	return 0;
}


