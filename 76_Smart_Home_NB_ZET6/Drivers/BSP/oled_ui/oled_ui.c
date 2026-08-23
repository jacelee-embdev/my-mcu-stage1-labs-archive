#include "oled_ui.h"
#include "oled.h"
#include "font_ui.h"

/* * 显示汉字
 */
void oled_show_interaction(uint8_t x, uint8_t y, uint8_t N, uint8_t message_type)
{
    uint16_t i, j;
    for(j = 0; j < 2; j++)
    {
        oled_set_cursor(x, y + j);
        for(i = 16 * j; i < 16 * (j + 1); i++)
        {
            switch(message_type)
            {
                case SHOW_INPUT_PWD:
                    oled_write_data(chinese_enter_password[N][i]);
                    break;
                
                case SHOW_PWD_RIGHT:
                    oled_write_data(chinese_password_right[N][i]);
                    break;
                
                case SHOW_PWD_WRONG:
                    oled_write_data(chinese_password_wrong[N][i]);
                    break;
                
                case SHOW_INPUT_OLD_PWD:
                    oled_write_data(chinese_enter_old_password[N][i]);
                    break;
                
                case SHOW_INPUT_NEW_PWD:
                    oled_write_data(chinese_enter_new_password[N][i]);
                    break;
                
                case SHOW_PWD_CHANGED:
                    oled_write_data(chinese_password_changed[N][i]);
                    break;
                
                case SHOW_SET_PWD:
                    oled_write_data(chinese_set_password[N][i]);
                    break;
                
                default:
                    break;
            }
        }
    }
}

//请输入密码
void oled_show_input(void)
{
    oled_fill(0x00);
    oled_show_interaction(10,1,0,SHOW_INPUT_PWD);
    oled_show_interaction(30,1,1,SHOW_INPUT_PWD);
    oled_show_interaction(50,1,2,SHOW_INPUT_PWD);
    oled_show_interaction(70,1,3,SHOW_INPUT_PWD);
    oled_show_interaction(90,1,4,SHOW_INPUT_PWD);
    oled_show_char(110,1,':',16);
}

//密码正确
void oled_show_right(void)
{
    oled_fill(0x00);
    oled_show_interaction(20,1,0,SHOW_PWD_RIGHT);
    oled_show_interaction(45,1,1,SHOW_PWD_RIGHT);
    oled_show_interaction(70,1,2,SHOW_PWD_RIGHT);
    oled_show_interaction(95,1,3,SHOW_PWD_RIGHT);
}

//密码错误
void oled_show_wrong(void)
{
    oled_fill(0x00);
    oled_show_interaction(20,1,0,SHOW_PWD_WRONG);
    oled_show_interaction(45,1,1,SHOW_PWD_WRONG);
    oled_show_interaction(70,1,2,SHOW_PWD_WRONG);
    oled_show_interaction(95,1,3,SHOW_PWD_WRONG);
}

//请输入旧密码
void oled_show_old(void)
{
    oled_fill(0x00);
    oled_show_interaction(10,1,0,SHOW_INPUT_OLD_PWD);
    oled_show_interaction(30,1,1,SHOW_INPUT_OLD_PWD);
    oled_show_interaction(50,1,2,SHOW_INPUT_OLD_PWD);
    oled_show_interaction(70,1,3,SHOW_INPUT_OLD_PWD);
    oled_show_interaction(90,1,4,SHOW_INPUT_OLD_PWD);
    oled_show_interaction(110,1,5,SHOW_INPUT_OLD_PWD);
}

//请输入新密码
void oled_show_new(void)
{
    oled_fill(0x00);
    oled_show_interaction(10,1,0,SHOW_INPUT_NEW_PWD);
    oled_show_interaction(30,1,1,SHOW_INPUT_NEW_PWD);
    oled_show_interaction(50,1,2,SHOW_INPUT_NEW_PWD);
    oled_show_interaction(70,1,3,SHOW_INPUT_NEW_PWD);
    oled_show_interaction(90,1,4,SHOW_INPUT_NEW_PWD);
    oled_show_interaction(110,1,5,SHOW_INPUT_NEW_PWD);
}

//请设定密码
void oled_show_set(void)
{
    oled_fill(0x00);
    oled_show_interaction(10,1,0,SHOW_SET_PWD);
    oled_show_interaction(30,1,1,SHOW_SET_PWD);
    oled_show_interaction(50,1,2,SHOW_SET_PWD);
    oled_show_interaction(70,1,3,SHOW_SET_PWD);
    oled_show_interaction(90,1,4,SHOW_SET_PWD);
    oled_show_char(110,1,':',16);
}

//密码修改成功
void oled_show_changed(void)
{
    oled_fill(0x00);
    oled_show_interaction(10,1,0,SHOW_PWD_CHANGED);
    oled_show_interaction(30,1,1,SHOW_PWD_CHANGED);
    oled_show_interaction(50,1,2,SHOW_PWD_CHANGED);
    oled_show_interaction(70,1,3,SHOW_PWD_CHANGED);
    oled_show_interaction(90,1,4,SHOW_PWD_CHANGED);
    oled_show_interaction(110,1,5,SHOW_PWD_CHANGED);
}
