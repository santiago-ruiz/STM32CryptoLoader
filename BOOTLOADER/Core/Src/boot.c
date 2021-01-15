#include "boot.h"

typedef enum{
	INIT,
	READING,
	ERASING,
	FLASHING,
	JUMPING,
	FAIL
}boot_state;

static bool boot_check_condition(void);
static void jump_to_app(void);


static boot_state state = INIT;
FIL bin_file;

void boot_fsm(void){
	switch(state){
		case INIT:
			//Check for specific condition to update firmware
			if(boot_check_condition())
				state = READING;
			else
				state = JUMPING;
			break;

		case READING:
			//Check if we can find the binary image
			if(image_open_binary(&bin_file))
				state = ERASING;
			else
				state = FAIL;
			break;

		case ERASING:
			//Erase application FLASH memory
			HAL_FLASH_Unlock();
			uint32_t size_of_file = f_size(&bin_file);
			uint32_t erase_address = 0x00;
			for (erase_address = APPLICATIONADDRESS; (erase_address < (APPLICATIONADDRESS + size_of_file)) && (erase_address < FLASH_ENDADDRESS); \
				 erase_address = erase_address + PAGE_SIZE){
				if (FLASH_LAYER_ErasePage (erase_address) != HAL_OK){
					state = FAIL;
					break;
				}
				HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			}

			state = FLASHING;
			break;

		case FLASHING:
			break;

		case JUMPING:
			f_close(&bin_file);
			jump_to_app();
			break;

		case FAIL:
			break;

		default:
			break;
	}
}

static bool boot_check_condition(void){
	//This function check for specific condition
	//e.g. a pin status or a button pressed for 2 seconds
	return true;
}

pFunction Jump_To_Application;
uint32_t JumpAddress;

static void jump_to_app(void){

	if (((*(__IO uint32_t*)APPLICATIONADDRESS) & 0x2FFE0000 ) == 0x20000000)
	{
	  /* Jump to user application */
	  JumpAddress = *(__IO uint32_t*) (APPLICATIONADDRESS + 4);
	  Jump_To_Application = (pFunction) JumpAddress;
	  /* Initialize user application's Stack Pointer */
	  __set_MSP(*(__IO uint32_t*) APPLICATIONADDRESS);
	  Jump_To_Application();
	}

}
