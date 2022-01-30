#include "pong.h"

sposta_paddle_t sposta;

racchetta_t racchetta[2];


void init_paddle(){
	racchetta[0].length = racchetta[1].length=30;
	racchetta[0].x0 = racchetta[1].x0=MAX_X/2-racchetta[1].length/2;
	racchetta[0].dir=0;
	racchetta[1].dir=-1;
	sposta.dx=4;
	sposta.sx=4;
}

void start_game(){
	int i;
	GUI_Text( (MAX_X-19*8)/2,MAX_Y-160,(uint8_t *) "Press Key1 to Start", Black, Black); 
	
	for(i = 0; i < 5 ; i++){
		LCD_DrawLine(i,0,i,MAX_Y,Red);
		LCD_DrawLine(MAX_X-i-1,0,MAX_X-i-1,MAX_Y,Red); 
	}
	init_movement();
	init_paddle();
	print_paddle(Green);
	initball();
	print_ball(Green);
	print_score1(White);
	print_score2(White);
	enable_timer(0);
	
	

	
}




void print_paddle(uint16_t Color){
	int i;
	for(i = 0; i < 10; i++){
		LCD_DrawLine(racchetta[0].x0, MAX_Y-32-9+i, racchetta[0].x0 + racchetta[0].length, MAX_Y - 32-9+i, Color);
		LCD_DrawLine(racchetta[1].x0, 32+i, racchetta[1].x0 + racchetta[1].length, 32+i, Color);
	}
}
void print_paddle1(uint16_t Color){
	int i;
	for(i = 0; i < 10; i++){
		LCD_DrawLine(racchetta[0].x0, MAX_Y-32-9+i, racchetta[0].x0 + racchetta[0].length, MAX_Y - 32-9+i, Color);
	}
}
void print_paddle2(uint16_t Color){
	int i;
	for(i = 0; i < 10; i++){
		LCD_DrawLine(racchetta[1].x0, 32+i, racchetta[1].x0 + racchetta[1].length, 32+i, Color);
	}
}


void move_paddle1(int shift){
	
	
		
	int r=0;
	int i,x0 = racchetta[r].x0;
	
	if(shift > 0){
		
		racchetta[r].dir=+1;
		for(i = 0; i < shift && x0+racchetta[r].length < MAX_X - 5-1; i++){
			LCD_DrawLine(racchetta[r].x0+i,MAX_Y-32-9,racchetta[r].x0+i,MAX_Y-32,Black);
			LCD_DrawLine(racchetta[r].x0+racchetta[r].length+i+1,MAX_Y-32-9,racchetta[r].x0+racchetta[r].length+i+1,MAX_Y-32,Green);
		  
			
			x0++;
			
		}
		racchetta[r].x0 = x0; 
		return;
	}
	if(shift < 0){
		
		racchetta[r].dir=-1;
		for(i=0; i < -shift && x0 > 5; i++){
		  
			LCD_DrawLine(racchetta[r].x0+racchetta[r].length-i,MAX_Y-32-9,racchetta[r].x0+racchetta[r].length-i,MAX_Y-32,Black);
			LCD_DrawLine(racchetta[r].x0-i-1,MAX_Y-32-9,racchetta[r].x0-i-1,MAX_Y-32,Green);
			x0--;
		}
	
}
	
	racchetta[r].x0 = x0; 
}
void move_paddle2(int shift){
	
	
	//sposta contains the number of shifts I shound do to the left or to the right 
	//since the velocity is constant I move by 4 pixel at a time
		
	int r=1;
	int i,x0 = racchetta[r].x0;
	
	if(shift > 0&&sposta.dx>0){
		sposta.dx--;
		racchetta[r].dir=+1;
		for(i = 0; i < shift && x0+racchetta[r].length < MAX_X - 5-1; i++){
			LCD_DrawLine(racchetta[r].x0+i,32+9,racchetta[r].x0+i,32,Black);
			LCD_DrawLine(racchetta[r].x0+racchetta[r].length+i+1,+32+9,racchetta[r].x0+racchetta[r].length+i+1,32,Green);
		  
			
			x0++;
			
		}
		racchetta[r].x0 = x0; 
	
		if(sposta.dx==0){
			racchetta[1].dir=-1;
		if(sposta.sx==0)
			sposta.dx=sposta.sx=3;
			}
		return;
	}
	

	if(shift < 0 && sposta.sx>0){
		racchetta[r].dir=-1;
		sposta.sx--;
		for(i=0; i < -shift && x0 > 5; i++){
		  
			LCD_DrawLine(racchetta[r].x0+racchetta[r].length-i,32+9,racchetta[r].x0+racchetta[r].length-i,32,Black);
			LCD_DrawLine(racchetta[r].x0-i-1,+32+9,racchetta[r].x0-i-1,+32,Green);
			x0--;
		}
		racchetta[r].x0 = x0; 
		
		if(sposta.sx==0){
			racchetta[1].dir=+1;
		if(sposta.dx==0)
			sposta.dx=sposta.sx=3;	
		}
		
	}
	if(sposta.dx==0&&sposta.sx==0){
			sposta.dx=sposta.sx=3; 
			//I continue to do 3 shifts to the right and 3 to the left once I reached the target destination  
}
	

	
}
void spostamento_paddle(int position)
{
	
	ball_t ball=getBall();
	
	
	int a;
	int b=0;
	
	b=position;
	a=racchetta[1].x0+racchetta[1].length/2; 
	
	if(b>a){ //the ball is at the right side of the paddle
		racchetta[1].dir=+1; //move to the right
		sposta.dx=(b-a)/4; //calcolo numero di spostamenti verso destra
		sposta.sx=0;	
	}
	else if(b<a){ //the ball is at the left side of the paddle
		racchetta[1].dir=-1; //move to the left
		sposta.dx=0;
		sposta.sx=(a-b)/4;
		
	}
	
	
	
	
	
}
racchetta_t getRacchetta1(void){
	return racchetta[0];
	
}
racchetta_t getRacchetta2(void){
	return racchetta[1];
	
}
sposta_paddle_t getSposta(){
	return sposta;
}
