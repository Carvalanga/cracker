#ifndef CRACKER_H
#define CRACKER_H

typedef unsigned char byte;
typedef unsigned long HASH;

enum CRACK_ERRORS
{
	NOTHING					  = -1,
	NO_ERROR 			   	  =  0,
	CANT_OPEN_FILE 		   	  =  1,
	INCORRECT_FILE_СONTENT 	  =  2,
	INCORRECT_BYTE_CHANGES 	  =  3,
	FILE_ERROR_WHILE_PATCHING =  4,
	FILE_ALREADY_HACKED		  =  5,
};

const HASH HASH_OF_INPUT_FILE   = 4397824868337832263L;
const HASH HASH_OF_OUTPUT_FILE  = 10560036777200463364L;

const char FILE_TO_CRACK_NAME[] = "CRACK.COM";

const int  OFFSET_TO_HACK   = 0x37;
const byte BYTES_TO_HACK[] 	= {0xEB, 0x56};


size_t 	     get_file_size(FILE* pfile);
CRACK_ERRORS crack();
HASH 		 calc_byte_hash(byte* data, size_t size);
int 		 change_bytes(byte* buf);

#endif