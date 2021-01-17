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
			if(image_open_binary())
				state = ERASING;
			else
				state = FAIL;
			break;

		case ERASING:
			//Erase application FLASH memory
			if(image_erase_flash())
				state = FLASHING;
			else
				state = FAIL;
			break;

		case FLASHING:
			if(image_flash_file())
				state = JUMPING;
			else
				state = FAIL;
			break;

		case JUMPING:
//			f_close(&bin_file);
			//Jump to the application
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
	  // Jump to user application
	  JumpAddress = *(__IO uint32_t*) (APPLICATIONADDRESS + 4);
	  Jump_To_Application = (pFunction) JumpAddress;
	  //Initialize user application's Stack Pointer
	  __set_MSP(*(__IO uint32_t*) APPLICATIONADDRESS);
	  Jump_To_Application();
	}

}
