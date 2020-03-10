/*	Author: rohanbadiga
 *  Partner(s) Name: vik
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ADC_H.h"
#include "ledmatrix7219d88.h"

int game(void){
    
    DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    //DDRD = 0xFF; PORTD = 0x00;
    
    int x, y, xy, t;
	unsigned char center, up, down, left, right = 0;
	
    ADC_Init();
    
    while(1) {
		x = ADC_Read(0);
		y = ADC_Read(1);
		xy = ADC_Read(2);
        if(y>600) { //upward
			up = 1;
			PORTB = 16;
	     }
	    else if(y<400) {//down
		    down = 1;
		    PORTB = 2;
	     }		
	    else if(x<400) {//right
		    right = 1;
		    PORTB = 8;
	     }	
	    else if(x>600) {//left
		    left = 1;
		    PORTB = 4;
	     }	
	    else { //middle
		    center = 1;
		    PORTB = 1;
	     }
	    
       center = up = down = left = right = 0;

	}
}

int main(void) {
  
    game();
    ledmatrix7219d88_init();
    
    uint8_t ledmatrix = 0;

	
	uint8_t p = 1;
	for(;;) {

		int8_t led = 0;
		//loop every matrix
		for(ledmatrix=0; ledmatrix<LEDMATRIX7219D88_MAXLEDMATRIX; ledmatrix++){
			//loop every led
			for(led=0; led<64; led++) {
				if(p)
					ledmatrix7219d88_setledon(ledmatrix, led);
				else
					ledmatrix7219d88_setledoff(ledmatrix, led);
				_delay_ms(50);
			}
			ledmatrix7219d88_resetmatrix(ledmatrix);
		}

		if(p)
			p = 0;
		else
			p = 1;

		_delay_ms(1000);
	}
   


    
}
