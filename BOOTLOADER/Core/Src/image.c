#include "image.h"

FATFS FatFs; 	//Fatfs handle
FIL file; 		//File handle
FRESULT fres; //Result after operations

bool image_open_binary(FIL* fil){
	//Mount
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
		return false;
	}
	//Try to open binary file
	fres = f_open(&file, BINARY_FILE_NAME, FA_READ);
	if (fres != FR_OK) {
		return false;
	}

	//Check if binary size file is correct
	uint32_t size_of_file = f_size(&file);
	if (size_of_file > FLASH_SIZE - BOOTLOADER_SIZE)
		return false;

	*fil = file;


	return true;
}

