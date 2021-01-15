#ifndef BOOT__H
#define BOOT__H

#include <stdbool.h>
#include "ff.h"
#include "image.h"
#include "build_config.h"
#include "flash_layer.h"

void boot_fsm(void);

#endif
