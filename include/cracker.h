#ifndef CRACKER_H
#define CRACKER_H

typedef unsigned char byte;
typedef unsigned long HASH;

enum CRACK_ERRORS
{
	NO_ERROR 			   = 0,
	CANT_OPEN_FILE 		   = 1,
	INCORRECT_FILE_СONTENT = 2,
	INCORRECT_BYTE_CHANGES = 3,
};

const HASH HASH_OF_INPUT_FILE   = 79634503;
const HASH HASH_OF_OUTPUT_FILE  = 0X0;

const char* FILE_TO_CRACK_NAME = "CRACK.COM";

size_t get_file_size(FILE* pfile);
// int is_file_exists(const char *path);
CRACK_ERRORS crack(FILE* file);
HASH calc_byte_hash(byte* data, size_t size);
int change_bytes(byte* buf);

#endif