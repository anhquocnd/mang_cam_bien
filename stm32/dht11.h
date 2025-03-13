#ifndef DHT11_H
#define DHT11_H

#include "stm32f10x.h"

#define DHT11_PORT      GPIOA
#define DHT11_PIN       GPIO_Pin_0

void TIM2_Init(void); //khoi tao timer 2
void Delay_us(uint32_t us); // tao do tre
void DHT11_Init(void);
uint8_t DHT11_Read_Bit(void); 
uint8_t DHT11_Read_Byte(void);
uint8_t DHT11_Read_Data(uint8_t *humidity, uint8_t *temperature);

#endif