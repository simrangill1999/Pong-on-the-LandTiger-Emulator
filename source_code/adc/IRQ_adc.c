/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../led/led.h"
#include "../pong.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current=0x00;   
unsigned short AD_last = 0xFF;     /* Last converted value               */

void ADC_IRQHandler(void) { 
  	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xF00);// 0xFFF);/* Read Conversion Result             */o
	
	
	if(AD_current < 0x300)
		move_paddle1(-getBall().shift_x-1);
	else if(AD_current < 0x600)
		move_paddle1(-3);
	else if(AD_current < 0xA00);
	else if(AD_current < 0xD00)
		move_paddle1(3);
	else move_paddle1(+getBall().shift_x+1);
  if(AD_current != AD_last){
		//LED_Off(AD_last*7/0xFFF);	  // ad_last : AD_max = x : 7 		LED_Off((AD_last*7/0xFFF));	
		//LED_On(AD_current*7/0xFFF);	// ad_current : AD_max = x : 7 		LED_On((AD_current*7/0xFFF));	
		
		AD_last = AD_current;
  }	
}
