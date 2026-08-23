#ifndef __HCSR04_H__
#define __HCSR04_H__

#define TRIG_PORT                   GPIOB
#define TRIG_PIN                    GPIO_PIN_6
#define TRIG_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define TRIG_HIGH()                 HAL_GPIO_WritePin(TRIG_PORT,TRIG_PIN,GPIO_PIN_SET)
#define TRIG_LOW()                  HAL_GPIO_WritePin(TRIG_PORT,TRIG_PIN,GPIO_PIN_RESET)

#define ECHO_PORT                   GPIOB
#define ECHO_PIN                    GPIO_PIN_7
#define ECHO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define ECHO_STATUS()               HAL_GPIO_ReadPin(ECHO_PORT,ECHO_PIN)

void hcsr04_init(void);
float get_length_from_hcsr04(void);

#endif
