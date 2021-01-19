#include "image.h"

//Only for testing
#if (AES128 == 1)
uint8_t key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
#elif (AES192 == 1)
uint8_t key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
				  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
#elif (AES256 == 1)
uint8_t key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
				  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
#endif
uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };


FATFS FatFs; 	//Fatfs handle
FIL file; 		//File handle
FRESULT fres; //Result after operations
//Binary file reading buffer
uint8_t RAM_Buf[BUFFER_SIZE] ={0x00};

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
	uint32_t buffer_size;

#if (CRYPTO == 1)
	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
#endif

	while(read < size_of_file){

		if(size_of_file < BUFFER_SIZE)
			buffer_size = size_of_file;
		else
			buffer_size = BUFFER_SIZE;

		//Read a block of binary data
		if((error_code = f_read(&file,RAM_Buf,buffer_size, (UINT*)&read_size)) != FR_OK)
			return false;

		read += read_size;

#if (CRYPTO == 1)
#if (TINY_AES == 1)
#if (CBC == 1)
		AES_CBC_decrypt_buffer(&ctx, RAM_Buf, buffer_size);
#endif
#endif
#endif


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
		Last_PGAddress += tmp_read_size;
	}

	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,RESET);

	if(read < size_of_file){
		return false;
	}
	HAL_FLASH_Lock();
	f_close(&file);
	return true;
}








