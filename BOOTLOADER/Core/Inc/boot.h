#ifndef BOOT__H
#define BOOT__H

#include <commands.h>
#include <stdbool.h>
#include "ff.h"
#include "build_config.h"

void boot_fsm(void);

#endif
