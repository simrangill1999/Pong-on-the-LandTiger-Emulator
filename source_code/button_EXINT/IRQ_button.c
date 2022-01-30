#include "button.h"
#include "lpc17xx.h"
#include "../RIT/RIT.h"
extern int down;
int key = -1;


void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	enable_RIT();
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */

	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	
		key = 0;
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	enable_RIT();
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	key = 1;
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	enable_RIT();
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection */
	key = 2;
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


