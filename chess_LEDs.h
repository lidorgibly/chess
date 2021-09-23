#ifndef _CHESS_LEDS_H
#define _CHESS_LEDS_H



void show_permitted_locations(_coordinates coo);

void LED_on_off(_coordinates coo, bool on_off);
void LED_off_all();

#endif