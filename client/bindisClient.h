#pragma once

#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

#include "../src/shared.h"

struct bd {
	uint8_t * buffer;
	uint8_t * keys;
	uint32_t  width;
	uint32_t  height;
	uint8_t   pages;
};

static inline uint8_t bindisInit(struct bd * bd){
	int mainfd, keyfd;
	
	if (bd->width == 0 || bd->height == 0){
		printf("Please set a non-zero value to width and height equal to the ones on your config file\n");
		return 1;
	} 


main:
	mainfd = shm_open(
			SHM_MAIN,
			O_EXCL | O_RDWR,
			S_IRWXO);

	if (mainfd == -1){
		if (errno == EEXIST){
			shm_unlink(SHM_MAIN); 
			goto main;
		}
		else return 1;
	}

keys:

	keyfd = shm_open(
			SHM_KEYS,
			O_EXCL | O_RDWR,
			S_IRWXO);
	if (keyfd == -1){
		if (errno == EEXIST){
			shm_unlink(SHM_KEYS);
			goto keys;
		}
		else return 1;
	}
	
	bd->pages = bd->height / CHAR_BIT;
	off_t size = bd->width * bd->pages;

	bd->buffer = (uint8_t *) mmap(
								NULL,
								size,
								PROT_READ | PROT_WRITE,
								MAP_SHARED,
								mainfd, 0
								);
	bd->keys = 	 (uint8_t *) mmap(
								NULL,
								1,
								PROT_READ | PROT_WRITE,
								MAP_SHARED,
								keyfd, 0
								);

	return 0;
}

static inline void bindisFinish(){
	shm_unlink(SHM_MAIN);
	shm_unlink(SHM_KEYS);
}
