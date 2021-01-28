#include "boot.h"

typedef enum{
	INIT,
	READING,
	ERASING,
	FLASHING,
	VERIFYING,
	JUMPING,
	FAIL
}boot_state;

static bool boot_check_condition(void);

static boot_state state = INIT;
extern volatile uint32_t ms_counter;

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
			if(command_open_binary())
				state = ERASING;
			else
				state = FAIL;
			break;

		case ERASING:
			//Erase application FLASH memory
			if(command_erase_flash()){
				state = FLASHING;
			}
			else
				state = FAIL;
			break;

		case FLASHING:
			if(command_flash_file())
				state = VERIFYING;
			else
				state = FAIL;
			break;

		case VERIFYING:
			if(command_verify_flash())
				state = JUMPING;
			else
				state = FAIL;
			break;


		case JUMPING:
			//Timer (checked in debug)
			ms_counter;
			//Jump to the application
			command_jump_to_application();
			break;


		case FAIL:
			//Do something to show error and jump to application
			while(1);
//			jump_to_app();
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


