#include "boot.h"

typedef enum{
	INIT,
	WAIT,
	ERASE,
	FLASH,
	JUMP,
	FAIL
}boot_state;

static bool boot_check_condition(void);

static boot_state state;

void boot_fsm(void){
	switch(state){
		case INIT:
			break;
		case WAIT:
			break;
		case ERASE:
			break;
		case FLASH:
			break;
		case JUMP:
			break;
		case FAIL:
			break;
		default:
			break;
	}
}

static bool boot_check_condition(void){
	return true;
}
