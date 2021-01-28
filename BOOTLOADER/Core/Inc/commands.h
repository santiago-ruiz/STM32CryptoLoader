#ifndef COMMAND__H
#define COMMAND__H

#include "fatfs.h"
#include <stdbool.h>
#include <string.h>
#include "tiny_aes.h"
#include "aes.h"
#include "build_config.h"
#include "flash_layer.h"


bool command_open_binary(void);
bool command_erase_flash(void);
bool command_flash_file(void);
bool command_verify_flash(void);
void command_jump_to_application(void);


#endif
