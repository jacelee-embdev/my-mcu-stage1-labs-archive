#ifndef __LCD1602_H__
#define __LCD1602_H__

void lcd1602_init(void);
void lcd1602_gpio_init(void);
void lcd1602_start(void);

void lcd1602_write_cmd(char cmd);
void lcd1602_write_data(char data_show);

void lcd1602_show_char(char row,char col,char data);
void lcd1602_show_char_string(char row,char col,char *string);

void lcd1602_display_smoke(float smoke_value);
void lcd1602_display_limit(float limit_value);
    
#endif
