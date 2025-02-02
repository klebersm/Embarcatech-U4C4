#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#include "./U4C4.h"

static volatile int i = 0;
static alarm_id_t inc_alm;
static alarm_id_t dec_alm;


void init_gpio() {
    // uint32_t pinMask = 0x00 || 0x01 << BUTTON_A || 0x01 << BUTTON_B; 
    // gpio_init_mask(pinMask);
    // gpio_set_dir_masked(pinMask, GPIO_IN);
    
    // gpio_pull_up(BUTTON_A);
    // gpio_pull_up(BUTTON_B);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(BUTTON_B);

    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    // gpio_init(12);
    // gpio_set_dir(12, GPIO_OUT);

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
}

int64_t increment(alarm_id_t id, void *user_data) {
    i++;
    if(i > 9) i = 0;
    return 0;
}

int64_t decrement(alarm_id_t id, void *user_data) {
    i--;
    if(i < 0) i = 9;
    return 0;
}

static void gpio_callback(uint gpio, uint32_t events) {
    if(gpio == BUTTON_A){
        if(events & 0x4)        //FALL EDGE
            dec_alm = add_alarm_in_ms(DEBOUNCE_MS, increment, NULL, false);
        else if(events & 0x8)   // RISE EDGE
            cancel_alarm(dec_alm); 
    }

    else if (gpio == BUTTON_B){
        if(events & 0x4) 
            inc_alm = add_alarm_in_ms(DEBOUNCE_MS, decrement, NULL, false);

        else if(events & 0x8)   // RISE EDGE
            cancel_alarm(inc_alm);
    }
}

bool repeat_callback(struct repeating_timer *t) {

}

int main()
{
    stdio_init_all();

    init_gpio();
    initNeoPixel();
    bool led = true;

    // struct repeating_timer timer;
    // add_repeating_timer_ms(1000, repeat_callback, NULL, &timer);

    while (true) {
        // uint32_t start_ms = to_ms_since_boot(get_absolute_time());
        // printf("Tempo absoluto: %d\n", start_ms);

        switch(i){
            case 0:
                renderMatrix(CHAR_0);
                break;
            case 1:
                renderMatrix(CHAR_1);
                break;
            case 2:
                renderMatrix(CHAR_2);
                break;
            case 3:
                renderMatrix(CHAR_3);
                break;
            case 4:
                renderMatrix(CHAR_4);
                break;
            case 5:
                renderMatrix(CHAR_5);
                break;
            case 6:
                renderMatrix(CHAR_6);
                break;
            case 7:
                renderMatrix(CHAR_7);
                break;
            case 8:
                renderMatrix(CHAR_8);
                break;
            case 9:
                renderMatrix(CHAR_9);
                break;
            default:
                break;
        }
        sleep_ms(100);

        led = !led;
        gpio_put(LED_R, led);
    }
}
