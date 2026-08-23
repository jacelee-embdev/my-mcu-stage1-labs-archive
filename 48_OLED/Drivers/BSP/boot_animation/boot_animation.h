#ifndef __BOOT_ANIMATION_H__
#define __BOOT_ANIMATION_H__

#include "stdint.h"

void oled_inverse_display(uint8_t enable);
void oled_start_animation(void);
void oled_desktop_run(void);

#endif
