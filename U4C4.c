#include <stdio.h>
#include "pico/stdlib.h"

#include "./U4C4.h"

void initGpio() {
    uint32_t pinMask = 0x00 || 0x01 << BUTTON_A || 0x01 << BUTTON_B; 
    gpio_init_mask(pinMask);
    gpio_set_dir_masked(pinMask, GPIO_IN);
    
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    gpio_init(13);
    gpio_set_dir(13, GPIO_OUT);

    gpio_init(12);
    gpio_set_dir(12, GPIO_OUT);
}

int main()
{
    stdio_init_all();

    initGpio();

    while (true) {
        if(gpio_get(BUTTON_A)) {
            gpio_put(13, true);
        }else {
            gpio_put(13, false);
        }

        if(gpio_get(BUTTON_B)) {
            gpio_put(12, true);
        }else {
            gpio_put(12, false);
        }
    }
}
