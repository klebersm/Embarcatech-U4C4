#ifndef __U4C4_H_
#define __U4C4_H_

#include "neopixel/neopixel.h"

#define BUTTON_A      5
#define BUTTON_B      6
#define BUTTON_J      22
#define BUZZER_A      21
#define BUZZER_B      10

#define LED_R         13

#define DEBOUNCE_MS   100

static void gpio_callback(uint gpio, uint32_t events);
bool repeat_callback(struct repeating_timer *t);
int64_t increment(alarm_id_t id, void *user_data);
int64_t decrement(alarm_id_t id, void *user_data);

#endif