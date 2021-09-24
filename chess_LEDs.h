#ifndef _CHESS_LEDS_H
#define _CHESS_LEDS_H

typedef enum {ON, OFF} _LED_state;


void show_permitted_locations(_coordinates coo);

void LED_on_off(_coordinates coo, _LED_state on_off);
void LED_off_all();

#endif