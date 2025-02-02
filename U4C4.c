#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#include "./U4C4.h"

static volatile int i = 0;
static alarm_id_t inc_alm;
static alarm_id_t dec_alm;


void init_gpio() {
    // Inicializa o Botão A como entrada em PULL UP
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    // Inicializa o Botão B como entrada em PULL UP
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(BUTTON_B);

    // Inicializa o pino do led vermelho como saída
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    // Habilita interrupções pros botões A e B
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
}

// Incrementa o valor de i
int64_t increment(alarm_id_t id, void *user_data) {
    i++;
    if(i > 9) i = 0;
    return 0;
}

// Decrementa o valor de i
int64_t decrement(alarm_id_t id, void *user_data) {
    i--;
    if(i < 0) i = 9;
    return 0;
}

static void gpio_callback(uint gpio, uint32_t events) {
    // Se o Evento aconteceu no Botão A
    if(gpio == BUTTON_A){
        // Cancela o alarme de incremento, caso exista algum
        cancel_alarm(inc_alm); 
        // Se o Evento foi do tipo FALL EDGE (Borda de descida)
        if(events & 0x4)
            inc_alm = add_alarm_in_ms(DEBOUNCE_MS, increment, NULL, false);
    }

    // Se o evento aconteceu no Botão B
    else if (gpio == BUTTON_B){
        // Cancela o alarme de decremento, caso exista algum
        cancel_alarm(dec_alm);
        // Se o Evento foi do tipo FALL EDGE (Borda de descida)
        if(events & 0x4)
            dec_alm = add_alarm_in_ms(DEBOUNCE_MS, decrement, NULL, false);

    }
}

int main()
{
    stdio_init_all();

    // Inicializa os pinos de IO
    init_gpio();

    // Inicializa a matriz de leds
    initNeoPixel();

    // Cria uma variável para ficar alternando o status do led vermelho
    bool led = true;

    while (true) {
        
        // Renderiza o caractere de acordo com o número armazenado em i
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

        // Insere um delay de 100ms
        sleep_ms(100);

        // Alterna o status do led vermelho
        led = !led;
        gpio_put(LED_R, led);
    }
}
