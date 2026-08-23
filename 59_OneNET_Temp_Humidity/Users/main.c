#include "sys.h"
#include "delay.h"
#include "led.h"
#include "uart1.h"
#include "dht11.h"
#include "esp8266.h"
#include "onenet.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    LedInit();
    uart1_init(115200);
    esp8266_init(115200);
    printf("Hello World!\n");
    
    printf("MQTT初始化...\r\n");
    mqtt_init();
    
    printf("MQTT连接...\r\n");
    mqtt_connect(MQTT_ClientID,MQTT_UserName,MQTT_PassWord);
    
    uint8_t data_send[512] = {0};
    uint8_t dht11_data[4] = {0};
    while(1)
    {
        memset(dht11_data,0,4);
        dht11_read_data(dht11_data);
        sprintf((char *)data_send,"{\"id\":\"1384\",\"version\":\"1.0\",\"params\":{\"CurrentTemperature\":{\"value\":%d.%d},\"CurrentHumidity\":{\"value\":%d.%d}}}",
            dht11_data[2],dht11_data[3],dht11_data[0],dht11_data[1]);
        mqtt_publish_data(POST_TOPIC,(char *)data_send,0);
        
        printf("湿度:%d.%dRH  ",dht11_data[0],dht11_data[1]);
        printf("温度:%d.%d℃\r\n",dht11_data[2],dht11_data[3]);
        delay_ms(3000);
        printf("\r\n发送心跳包\r\n");
        mqtt_send_heart();
    }
}

