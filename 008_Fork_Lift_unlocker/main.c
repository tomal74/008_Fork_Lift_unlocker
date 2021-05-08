/*
 * main.c
 *
 *  Created on: 6 maj 2021
 *      Author: Tomasz Konieczka
 *
 *      Automatyczne odblokowanie paleciaka - Jan Grabianowski - Wyszyny
 *
 *      Usterka klaiatury paleciaka elektrycznego - ustawione has³o na 4444 i dodany ATtiny8,
 *      ktory przez tarsoptory zwiera 4x przycisk 4 i 1x przycisk ok
 */


// FCPU - 1MHz internal RC osc.

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>

#define FOUR_PIN (1<<PB3)	// klawisz 4 --> kod ustawilem na 4444
#define OK_PIN   (1<<PB4)	// klawisz zatwierdz --> OK

#define KEY_REPEAT 4	// dla pewnosci kliknij raz wiecej

#define RELEASE_DELAY 50 	// 30 + 20zapasu (patrz czestotliwosc wew. gen. RC vs temperatura)
#define PUSH_DELAY 40		// 20 + 20zapasu


void four_key_click(void);
void ok_key_click(void);

int main(void) {

	DDRB |= FOUR_PIN | OK_PIN;	// set PB4 and PB3 as outputs

	_delay_ms(2000);	// wait for forklift display boot-up

	for(uint8_t i=0; i<KEY_REPEAT; i++) {
		four_key_click();
	}

	ok_key_click();

	// go sleep until next power reset (block mcu)
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_mode();
	while(1) {

	}
}



void four_key_click(void) {
	PORTB |= FOUR_PIN;
	_delay_ms(PUSH_DELAY);
	PORTB &= ~FOUR_PIN;
	_delay_ms(RELEASE_DELAY);
}


void ok_key_click(void) {
	PORTB |= OK_PIN;
	_delay_ms(PUSH_DELAY);
	PORTB &= ~OK_PIN;
	_delay_ms(RELEASE_DELAY);
}
