#include <sys/mman.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>

#include "bindisClient.h"

int main(int argc, char * argv[]){
	//bindis initialization process, please set the same resolution values
	//   that you wrote on your config file.
	struct bd bd;
	bd.width  = 128;
	bd.height = 64;
	if (bindisInit(&bd)) return 1;


	bd.buffer[0] = 0b1;

	

	return 0;
}
