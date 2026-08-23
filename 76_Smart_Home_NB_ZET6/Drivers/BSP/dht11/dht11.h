#ifndef __DHT11_H__
#define __DHT11_H__

#include "sys.h"

#define HIGH    1
#define LOW     0

#define DHT11_PORT              GPIOB
#define DHT11_PIN               GPIO_PIN_1
#define DHT11_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define DHT11_DQ_OUT(x)         do{x? \
                                    HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_SET): \
                                    HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_RESET); \
                                }while(0)

#define DHT11_DQ_IN             HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN)
void dht11_read_data(uint8_t *result);
#endif
