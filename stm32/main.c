#include "dht11.h"

int main(void) {
    uint8_t humidity, temperature;

    DHT11_Init(); 

    while (1) {
        if (DHT11_Read_Data(&humidity, &temperature)) {
  
          
        }
        else {
          
        }
        Delay_us(2000000);
    }
}