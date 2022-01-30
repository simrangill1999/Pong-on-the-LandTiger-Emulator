/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "adc/adc.h"
#include "GLCD/GLCD.h"
#include "TouchPanel/TouchPanel.h"
#include "pong.h"
#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
volatile int score[2]={0};




int main (void) {
	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
	BUTTON_init();
  LED_init();                           /* LED Initialization                 */
 
	
	
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       	*/
	
	LCD_Initialization();
	TP_Init();
	ADC_init();
		
	
	
	init_timer(0,0x004C4B40);    //50 ms

	
	LCD_Clear(Black); 
	

	GUI_Text( (MAX_X-8*4)/2,MAX_Y-160-18,(uint8_t *) "PONG", White, Blue); 
	
	
	GUI_Text( (MAX_X-19*8)/2,MAX_Y-160,(uint8_t *) "Press Key1 to Start", White, Blue); 
	GUI_Text( (MAX_X-8*4)/2,MAX_Y-160-18,(uint8_t *) "PONG", Black, Black); 
	
	
	NVIC_DisableIRQ(EINT0_IRQn);
	NVIC_DisableIRQ(EINT2_IRQn);
	NVIC_EnableIRQ(EINT1_IRQn);
	
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
	
	
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
	
  while (1) {                           /* Loop forever                       */	
//		__ASM("wfi");
  }

}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
