#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "cracker.h"

int main()
{
	printf("result = %d\n", run_crack());
	return 0;
}

size_t get_file_size(FILE* pfile)
{
    struct stat st = {};
    fstat(fileno(pfile), &st);

    return st.st_size;
}

// int is_file_exists(const char *path)
// {
//     struct stat st;

//     stat(path, &st);

//     if (st.st_mode)
//         return 1;

//     return 0;
// }

CRACK_ERRORS run_crack()
{
	FILE* file = fopen(FILE_TO_CRACK_NAME, "r+b");
	if(!file)
		return CANT_OPEN_FILE;

	CRACK_ERRORS err_code = crack(file);
	fclose(file);

	return err_code;
}

static CRACK_ERRORS crack(FILE* file)
{
	size_t file_size = get_file_size(file);
	byte* buf = (byte*)calloc(file_size, sizeof(byte));
	fread(buf, sizeof(byte), file_size, file);

	printf("HASH = %d\n", calc_byte_hash(buf, file_size));

	if(calc_byte_hash(buf, file_size) != HASH_OF_INPUT_FILE)
		return INCORRECT_FILE_СONTENT;

	change_bytes(buf);

	if(calc_byte_hash(buf, file_size) != HASH_OF_OUTPUT_FILE)
		return INCORRECT_BYTE_CHANGES;

	fwrite(buf, sizeof(byte), file_size, file);

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
	//change bytes to make any password correct
	//((3 * 16 + 8) - 1) - correct offset

	byte hack[] = {0xEB, 0x56};
	for(int i = 0; i < sizeof(hack); i++)
		buf[3*16 + 7 + i] = hack[i];

	return 0;
}
