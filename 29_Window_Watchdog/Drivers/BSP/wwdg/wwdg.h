#ifndef __WWDG_H__
#define __WWDG_H__

#include "sys.h"

void wwdg_init(uint8_t tr,uint8_t wr,uint32_t psc);
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg);
void wwdg_feed(void );

#endif
