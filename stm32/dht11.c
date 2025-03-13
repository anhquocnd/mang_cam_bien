#include "dht11.h"

void TIM2_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Bat clock cho Timer 2
    TIM2->PSC = 71; // Prescaler = 71 -> 72MHz / 72 = 1MHz (1 tick = 1µs)
    TIM2->ARR = 0xFFFF; 
    TIM2->CR1 |= TIM_CR1_CEN; // Bat Timer
}


void Delay_us(uint32_t us) {
    TIM2->CNT = 0; // Reset counter
    while (TIM2->CNT < us); 
}


void DHT11_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

    GPIO_InitStruct.GPIO_Pin = DHT11_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(DHT11_PORT, &GPIO_InitStruct);

    TIM2_Init(); 
}


uint8_t DHT11_Read_Bit(void) {
    uint8_t bit = 0;
    Delay_us(50); 
    if (DHT11_PORT->IDR & DHT11_PIN) { 
        Delay_us(30); 
        if (DHT11_PORT->IDR & DHT11_PIN) { 
            bit = 1; // Bit 1 (xung cao > 26µs)
        }
    }
    while (DHT11_PORT->IDR & DHT11_PIN); 
    return bit;
}


uint8_t DHT11_Read_Byte(void) {
    uint8_t byte = 0;
    for (uint8_t i = 0; i < 8; i++) {
        byte |= (DHT11_Read_Bit() << (7 - i));
    }
    return byte;
}


uint8_t DHT11_Read_Data(uint8_t *humidity, uint8_t *temperature) {
    uint8_t data[5];
    GPIO_InitTypeDef GPIO_InitStruct;


    DHT11_PORT->BRR = DHT11_PIN; 
    Delay_us(18000); 
    DHT11_PORT->BSRR = DHT11_PIN; // Kéo cao
    Delay_us(30);


    GPIO_InitStruct.GPIO_Pin = DHT11_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // Input pull-up
    GPIO_Init(DHT11_PORT, &GPIO_InitStruct);

    Delay_us(40); 
    if (!(DHT11_PORT->IDR & DHT11_PIN)) { 
        Delay_us(80); 
        if (DHT11_PORT->IDR & DHT11_PIN) { // DHT11 kéo cao
            Delay_us(80); 


            for (uint8_t i = 0; i < 5; i++) {
                data[i] = DHT11_Read_Byte();
            }

   
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
            GPIO_Init(DHT11_PORT, &GPIO_InitStruct);


            if (data[4] == (data[0] + data[1] + data[2] + data[3])) {
                *humidity = data[0]; 
                *temperature = data[2]; 
                return 1; 
            }
        }
    }
    return 0; 
}