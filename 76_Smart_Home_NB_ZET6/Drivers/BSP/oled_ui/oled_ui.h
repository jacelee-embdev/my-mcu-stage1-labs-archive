#ifndef __OLED_UI_H__
#define __OLED_UI_H__

#include "sys.h"
enum message{
    SHOW_INPUT_PWD = 0,
    SHOW_PWD_RIGHT,
    SHOW_PWD_WRONG,
    SHOW_INPUT_OLD_PWD,
    SHOW_INPUT_NEW_PWD,
    SHOW_PWD_CHANGED,
    SHOW_SET_PWD
};

void oled_show_input(void);
void oled_show_right(void);
void oled_show_wrong(void);
void oled_show_old(void);
void oled_show_new(void);
void oled_show_set(void);
void oled_show_changed(void);

#endif
