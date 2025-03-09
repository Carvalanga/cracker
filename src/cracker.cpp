#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cracker.h"


size_t get_file_size(FILE* pfile)
{
    struct stat st = {};
    fstat(fileno(pfile), &st);

    return st.st_size;
}

CRACK_ERRORS crack()
{
	FILE* file = fopen(FILE_TO_CRACK_NAME, "rb");
	if(!file)
		return CANT_OPEN_FILE;

	size_t file_size = get_file_size(file);
	byte* buf = (byte*)calloc(file_size, sizeof(byte));
	fread(buf, sizeof(byte), file_size, file);

	fclose(file);

	HASH input_hash = calc_byte_hash(buf, file_size);

	if(input_hash == HASH_OF_OUTPUT_FILE)
		return FILE_ALREADY_HACKED;

	if(input_hash != HASH_OF_INPUT_FILE)
		return INCORRECT_FILE_СONTENT;

	memcpy(buf + OFFSET_TO_HACK, BYTES_TO_HACK, sizeof(BYTES_TO_HACK) / sizeof(BYTES_TO_HACK[0]));

	if(calc_byte_hash(buf, file_size) != HASH_OF_OUTPUT_FILE)
		return INCORRECT_BYTE_CHANGES;

	file = fopen(FILE_TO_CRACK_NAME, "wb");

	if(!file)
		return FILE_ERROR_WHILE_PATCHING;
	fwrite(buf, sizeof(byte), file_size, file);

	fclose(file);
	free(buf);

	return NO_ERROR;
}

HASH calc_byte_hash(byte* data, size_t size)
{
	HASH hash = 5381;

	for(int i = 0; i < size; i++)
		hash = ((hash << 5) + hash) + data[i];

	return hash;
}

int change_bytes(byte* buf)
{
	byte hack[] = {0xEB, 0x56};
	for(int i = 0; i < sizeof(hack); i++)
		buf[3*16 + 7 + i] = hack[i];

	return 0;
}
