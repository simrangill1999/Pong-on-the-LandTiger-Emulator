/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../timer/timer.h"
#include "../pong.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
** cosa sei sola menomale
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern int key;
extern int score[2];
extern int record;
extern int lose;
extern int first;
int pause=0;
void RIT_IRQHandler (void)
{			
	static int down=0;	

	//NVIC_ClearPendingIRQ(EINT0_IRQn);
	//NVIC_ClearPendingIRQ(EINT1_IRQn);
	//NVIC_ClearPendingIRQ(EINT2_IRQn);
		
		
		reset_RIT();
		switch(key){
			case 0: //INT0
				if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
					
					//NVIC_DisableIRQ(EINT0_IRQn);
					down++;
					if(down==1){		
						disable_timer(0);	
						lose=0;
						score[0]=score[1]=0;
						LCD_Clear(Black);					
						first=1;
						GUI_Text( (MAX_X-19*8)/2,MAX_Y-160,(uint8_t *) "Press Key1 to Start", White, Blue); 
						//NVIC_DisableIRQ(EINT2_IRQn);
						//NVIC_DisableIRQ(EINT0_IRQn);
						NVIC_ClearPendingIRQ(EINT1_IRQn);
						NVIC_ClearPendingIRQ(EINT2_IRQn);
						NVIC_EnableIRQ(EINT1_IRQn);
						NVIC_SetPendingIRQ(EINT1_IRQn);
						
					}
					}
				else {	/* button released */
				down=0;	
				key=-1;					
				disable_RIT();
				reset_RIT();
				NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
				}
				break;
			case 1: //key1
				if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
					down++;
					if(down==1){
						start_game();
						NVIC_DisableIRQ(EINT1_IRQn);
						NVIC_ClearPendingIRQ(EINT0_IRQn);
						NVIC_ClearPendingIRQ(EINT2_IRQn);
						NVIC_DisableIRQ(EINT0_IRQn);
						NVIC_EnableIRQ(EINT2_IRQn);
						NVIC_SetPendingIRQ(EINT2_IRQn);
					}
					}
				else {	/* button released */
				down=0;	
				key=-1;					
				disable_RIT();
				reset_RIT();
				NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
				}
				break;
			case 2:
				if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
					down++;
					if(down==1){
						NVIC_ClearPendingIRQ(EINT1_IRQn);
						NVIC_ClearPendingIRQ(EINT0_IRQn);
						if(pause==0){
							disable_timer(0);	
							pause=1;
							GUI_Text( (MAX_X-10-5*8)/2+5,MAX_Y-16,(uint8_t *) "PAUSE",White, Blue);
						}
						else {enable_timer(0);
								GUI_Text( (MAX_X-10-5*8)/2+5,MAX_Y-16,(uint8_t *) "PAUSE",Black, Black);
									pause=0;}
					}
				}
				else {	/* button released */
				down=0;	
				key=-1;					
				disable_RIT();
				reset_RIT();
				NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
				}
				break;
			default:
				down=0;
				key=-1;
				LPC_PINCON->PINSEL4    |= (1 << 20);  
				LPC_PINCON->PINSEL4    |= (1 << 22);  
				LPC_PINCON->PINSEL4    |= (1 << 24); 
				disable_RIT();
				reset_RIT();
				
				break;
		}
	
		//reset_RIT();
		
		

  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
