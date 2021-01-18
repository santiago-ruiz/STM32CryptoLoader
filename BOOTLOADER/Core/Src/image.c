#include "image.h"

FATFS FatFs; 	//Fatfs handle
FIL file; 		//File handle
FRESULT fres; //Result after operations
//Binary file reading buffer
uint8_t RAM_Buf[BUFFER_SIZE] =
  {
    0x00
  };

bool image_open_binary(void){
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

	return true;
}

bool image_erase_flash(void){
	HAL_FLASH_Unlock();
	uint32_t size_of_file = f_size(&file);
	uint32_t erase_address = 0x00;
	for (erase_address = APPLICATIONADDRESS; (erase_address < (APPLICATIONADDRESS + size_of_file)) && (erase_address < FLASH_ENDADDRESS); \
		 erase_address = erase_address + PAGE_SIZE){
		if (FLASH_LAYER_ErasePage (erase_address) != HAL_OK){
			return false;
		}
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	}
	return true;
}

bool image_flash_file(void){
	uint32_t read = 0;
	uint32_t size_of_file = f_size(&file);
	uint8_t error_code;
	//RAM Address Initialization
	uint32_t ram_address = (uint32_t) & RAM_Buf;
	//Erase address init
	uint32_t Last_PGAddress = APPLICATIONADDRESS;
	uint32_t tmp_program_counter = 0x00, tmp_read_size = 0x00;
	__IO uint32_t program_counter = 0x00, read_size = 0x00;


	while(read < size_of_file){

		//Read a block of binary data
		if((error_code = f_read(&file,RAM_Buf,BUFFER_SIZE, (UINT*)&read_size)) != FR_OK)
			return false;

		read += read_size;

		//Temp variable
		tmp_read_size = read_size;

		//Program flash memory
		for (program_counter = tmp_read_size; program_counter != 0; program_counter -= 4)
		{
			tmp_program_counter = program_counter;
			//Write word into flash memory
			if (FLASH_LAYER_ProgramWord((Last_PGAddress - tmp_program_counter + tmp_read_size), \
									  *(__IO uint32_t *)(ram_address - program_counter + tmp_read_size)) != HAL_OK)
			{
				return false;
			}
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		}
		//Update last programmed address value
		Last_PGAddress = Last_PGAddress + tmp_read_size;
	}

	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,RESET);

	if(read < size_of_file){
		return false;
	}
	HAL_FLASH_Lock();
	f_close(&file);
	return true;
}


bool image_decrypt_binary(void){

	uint8_t key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
//	uint8_t in[]  = { 0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46, 0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d,
//					  0x50, 0x86, 0xcb, 0x9b, 0x50, 0x72, 0x19, 0xee, 0x95, 0xdb, 0x11, 0x3a, 0x91, 0x76, 0x78, 0xb2,
//					  0x73, 0xbe, 0xd6, 0xb8, 0xe3, 0xc1, 0x74, 0x3b, 0x71, 0x16, 0xe6, 0x9e, 0x22, 0x22, 0x95, 0x16,
//					  0x3f, 0xf1, 0xca, 0xa1, 0x68, 0x1f, 0xac, 0x09, 0x12, 0x0e, 0xca, 0x30, 0x75, 0x86, 0xe1, 0xa7 };
	uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
//	uint8_t out[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
//					  0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
//					  0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
//					  0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10 };
#define SIZE_READ	512
	uint8_t in[SIZE_READ];
	uint32_t read_size=0;
	f_read(&file,in,SIZE_READ, (UINT*)&read_size);

	struct AES_ctx ctx;

	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_decrypt_buffer(&ctx, in, SIZE_READ);

	return true;
}







