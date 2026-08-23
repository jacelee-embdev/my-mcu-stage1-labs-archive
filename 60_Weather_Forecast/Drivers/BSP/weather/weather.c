#include "weather.h"
#include "esp8266.h"
#include "string.h"
#include "cJSON.h"
#include "stdio.h"
#include "delay.h"
#include "oled.h"
#include "stdlib.h"

char weather_data[ESP8266_RX_BUF_SIZE] = {0};

typedef struct
{
    char date[20];
    char code_day[10];
    char high[10];
    char low[10];
}daily_weather_t;

daily_weather_t three_day_weather[3] ={0};

void get_3days_weather(void)
{
    uint8_t i = 0;
    for(i = 0; i < 3; i++)
    {
        memset(weather_data,0,sizeof(weather_data));
        esp8266_get_weather(i);
        esp8266_copy_rxdata(weather_data);
        
        //1. 将JSON字符串转换成JSON结构体
        cJSON *cjson = cJSON_Parse((const char *)weather_data);
        
        //2. 解析JSON各个字段
            //2.1 获取根对象里的results字段的值(数组1)
            cJSON *cjson_results = cJSON_GetObjectItem(cjson,"results");
        
            //2.2 获取数组1的第一个元素(对象1)
            cJSON *results_first = cJSON_GetArrayItem(cjson_results,0);
        
            //2.3 获取对象1的daily字段的值(数组2)
            cJSON *daily = cJSON_GetObjectItem(results_first,"daily");
        
            //2.4 获取数组2的第一个元素(对象2)
            cJSON *daily_first = cJSON_GetArrayItem(daily,0);
        
            //2.5 获取对象2中的date字段的值
            cJSON *date = cJSON_GetObjectItem(daily_first,"date");
            const char *date_str = date->valuestring;
            strcpy(three_day_weather[i].date,date_str);
            printf("date:%s\r\n",date_str);
            
            //2.6 获取对象2中的code_day字段的值
            cJSON *code_day = cJSON_GetObjectItem(daily_first,"code_day");
            const char *code_day_str = code_day->valuestring;
            strcpy(three_day_weather[i].code_day,code_day_str);
            printf("code_day:%s\r\n",code_day_str);
            
            //2.7 获取对象2中的high字段的值
            cJSON *high = cJSON_GetObjectItem(daily_first,"high");
            const char *high_str = high->valuestring;
            strcpy(three_day_weather[i].high,high_str);
            printf("high:%s\r\n",high_str);
            
            //2.8 获取对象2中的low字段的值
            cJSON *low = cJSON_GetObjectItem(daily_first,"low");
            const char *low_str = low->valuestring;
            strcpy(three_day_weather[i].low,low_str);
            printf("low:%s\r\n\r\n\r\n",low_str);
            
        //3. 清除JSON结构体
        cJSON_Delete(cjson);
        
        delay_ms(100);
    }
}

void show_weather(uint8_t day)
{
    oled_show_init();
    
    oled_show_string(10,0,three_day_weather[day].date,16);
    uint8_t code_day= atoi(three_day_weather[day].code_day);
    switch (code_day)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            oled_show_Chinese(77, 2, 8);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            oled_show_Chinese(77, 2, 9);
            oled_show_Chinese(77+18, 2, 10);
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            oled_show_Chinese(77, 2, 12);
            break;
    }
    
    oled_show_string(77,4,three_day_weather[day].high,16);
    oled_show_string(77,6,three_day_weather[day].low,16);
}
