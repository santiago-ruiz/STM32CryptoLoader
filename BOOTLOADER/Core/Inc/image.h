#ifndef IMAGE__H
#define IMAGE__H

#include "fatfs.h"
#include <stdbool.h>
#include "build_config.h"

bool image_open_binary(FIL* fil);

#endif
