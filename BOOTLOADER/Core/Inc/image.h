#ifndef IMAGE__H
#define IMAGE__H

#include "fatfs.h"
#include <stdbool.h>
#include "tiny_aes.h"
#include "build_config.h"

bool image_open_binary(void);
bool image_erase_flash(void);
bool image_flash_file(void);

#endif
