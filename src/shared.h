#pragma once

#define SHM_MAIN "/bd"
#define SHM_KEYS "/bdkeys"

//keys

#define KEY_Q 0b00000001
#define KEY_A 0b00000010
#define KEY_B 0b00000100
#define KEY_C 0b00001000
#define KEY_D 0b00010000
#define KEY_E 0b00100000
#define KEY_F 0b01000000
#define KEY_G 0b10000000

#define BYTE_SIZE 			8


#define MStoNS 			1000000
#define DEFAULT_ITIME 	1/60*1000* MStoNS
