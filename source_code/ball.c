#include "pong.h"
#include "stdio.h"
#include "RIT/RIT.h"
ball_t ball;
extern int score[2];
//extern int record;
extern int lose;
int first=0;

const int freqs[8]={2120,1890,1684,1592,1417,1263,1125,1062};


void initball(){
	ball.x0=MAX_X-5-5;
	ball.y0=160;
	ball.dir_x=+1;
	ball.dir_y=+1;
	ball.shift_x=5;
	ball.shift_y=5;

	
}
typedef struct{
	int shift_x;
	int shift_y;
}move_t;
 move_t movement[5];
 void init_movement(){
	 
	 int i;
	 movement[2].shift_x=movement[2].shift_y=5;
	 for(i=0;i<2;i++){
		movement[i].shift_y=(2-i)*2+5;
		movement[i].shift_x=movement[4-i].shift_y=5;
		movement[4-i].shift_x=(2-i)*2+5;
	 }		 
	 
	 
 }

void print_ball(uint16_t Color){
		int i;
		

	for(i=0;i<5;i++)
		LCD_DrawLine(ball.x0+i,ball.y0,ball.x0+i,ball.y0+4,Color);
	
}
void print_score1(uint16_t Color){
		char text[sizeof(score[0])+1];
		sprintf(text," %d",score[0]);
		GUI_Text(5,MAX_Y-160,(uint8_t *) text,Color,Black);	
}
void print_score2(uint16_t Color){
		char text[sizeof(score[1])+1];
		sprintf(text,"%d",score[1]);
		GUI_Text2(MAX_X-5-8,MAX_Y-160+16,(uint8_t *) text,Color,Black);	
}




void part_paddle(int x,racchetta_t racchetta){
	
	
	int x0=racchetta.x0;
	int x1=x0+racchetta.length;
	int dir=racchetta.dir;
	int m=racchetta.length/2;
	int p;
	
	ball.dir_x=dir;
	if(x>=x0+m-1 && x<=x0+m+1)
		p=0;
	
	else if(x<=x0+4){
			
		if(ball.x0==5)
			ball.dir_x=+1;
		p=-2;
	
	}
	else if(x>x0+4 && x<x0+m-1)
		p=-1;
		
	
	else if(x>=x1-4){
			
		if(ball.x0+4==MAX_X-5-1)
			ball.dir_x=-1;
		p=+2;
		
	}
	else p=+1;
		
		
	
	
		ball.shift_x=movement[2+p*dir].shift_x;
	if(dir!=ball.dir_x&&ball.shift_x>5)
		ball.shift_x-=1;
		ball.shift_y=movement[2+p*dir].shift_y;
	if(dir!=ball.dir_x &&ball.shift_y>5)
		ball.shift_y-=1;
	
	
}

void move_ball(){
	int i,x0,x1,sposta_x,sposta_y,flag=0,a,b=0;
	int dir;
	char stringa[20];
	racchetta_t racchetta=getRacchetta1();
	if(ball.y0<MAX_Y*2&&ball.dir_y==-1){ 
		racchetta=getRacchetta2(); 
		flag=1;}
	x0=racchetta.x0;
	x1=x0+racchetta.length;
	sposta_x=ball.shift_x;
	sposta_y=ball.shift_y;
	
	if(flag==1){
	if(ball.y0<32+9-1){ 
		if(ball.y0+ball.dir_y*ball.shift_y<=5|| ball.x0+ball.dir_x*ball.shift_x>=MAX_X-5 || ball.x0+ball.dir_x*ball.shift_x<=5){
		disable_timer(0);
		print_score1(Black);
		score[0]++;
		print_score1(White);
		if(score[0]==5){ 
			lose=1;
			GUI_Text((MAX_X-8*7)/2, MAX_Y-160+16,(uint8_t *) "You win", Red, Black);	
			sprintf(stringa,"Score: %d",score[0]);
			GUI_Text( (MAX_X-8*7)/2,MAX_Y-160+18+16,(uint8_t *) stringa,Yellow, Black);
			GUI_Text2((MAX_X-10+8*8)/2, MAX_Y-160-2,(uint8_t *) "You lose", Red, Black);
			sprintf(stringa,"Score: %d",score[1]);
			GUI_Text2( (MAX_X-10+8*8)/2,MAX_Y-160-2-18,(uint8_t *) stringa,Yellow, Black);
			GUI_Text( (MAX_X-10-21*8)/2+5,MAX_Y-160,(uint8_t *) "Press Int0 to Restart",White, Blue); 
			NVIC_ClearPendingIRQ(EINT0_IRQn);
			NVIC_ClearPendingIRQ(EINT1_IRQn);
			NVIC_ClearPendingIRQ(EINT2_IRQn);
			NVIC_EnableIRQ(EINT0_IRQn);
			NVIC_SetPendingIRQ(EINT0_IRQn);
			NVIC_DisableIRQ(EINT1_IRQn);
			NVIC_DisableIRQ(EINT2_IRQn);
					
		}
		else {
			first=1;
			print_paddle(Black);
			print_ball(Black);
			init_paddle();
			print_paddle(Green);
			initball();
			print_ball(Green);
			enable_timer(0);
			
		}
		
		return;
		
	}
		if((ball.x0+4==x0-1 || ball.x0==x1+1) && (ball.y0>=32)){
			dir=ball.dir_x;
			ball.dir_x=-dir;
			ball.shift_x=sposta_x=5+4;
			ball.shift_y=sposta_y=5;
			
		}
		if(-(ball.x0+ball.dir_x*(ball.shift_x+4))+x0<5  && -(ball.x0+ball.dir_x*(ball.shift_x+4))+x0>-14&&(ball.y0+ball.dir_y*ball.shift_y+4>=32 || ball.y0+ball.dir_y*ball.shift_y>=32)){
			sposta_x+=x0-(ball.x0+ball.dir_x*ball.shift_x+4)-1; //it the ball hits exactly the border of the paddle
		}
		else if((ball.x0+ball.dir_x*(ball.shift_x))-x1<5 && (ball.x0+ball.dir_x*(ball.shift_x))-x1>-14&&(ball.y0+ball.dir_y*ball.shift_y+4>=32 || ball.y0+ball.dir_y*ball.shift_y>=32 )){
			sposta_x+=-x1+(ball.x0+ball.dir_x*ball.shift_x)-1; //the paddle moves in order to hit the ball
		}
		
		for(i=0;i<5;i++){
		
		
		LCD_DrawLine(ball.x0+i,ball.y0,ball.x0+i,ball.y0+4,Black);
		LCD_DrawLine(ball.x0+ball.dir_x*sposta_x+i,ball.y0+ball.dir_y*sposta_y,ball.x0+ball.dir_x*sposta_x+i,ball.y0+ball.dir_y*sposta_y+4,Green);
	}
		if((ball.x0<=x1 && ball.x0>=x0) || (ball.x0+4*ball.dir_x<=x1 && ball.x0+4*ball.dir_x>=x0) && (ball.y0>=32 || ball.y0+4>=32) )
			print_paddle2(Green); 
		
		ball.x0+=ball.dir_x*sposta_x;
		ball.y0+=ball.dir_y*sposta_y;
		if(ball.x0+ball.shift_x*ball.dir_x<5 || ball.x0+ball.shift_x*ball.dir_x+4>MAX_X-5 ) //if the next position is out of the display
			ball.shift_y=ball.y0; 
		return;
		
	}
	
	if((ball.y0+ball.dir_y*(ball.shift_y)<+32+9+5)&&(((ball.x0+ball.shift_x*ball.dir_x<=x1)&&(ball.x0+ball.shift_x*ball.dir_x>=x0))||((ball.x0<=x1)&&(ball.x0>=x0))|| ((ball.x0+4<=x1)&&(ball.x0+4>=x0))))
	{
		
		if(ball.y0==+32+9+1){
				init_timer(1,500);
				enable_timer(1);
			
				ball.dir_y=+1;
				part_paddle(ball.x0,racchetta);
				spostamento_paddle(MAX_X/2-racchetta.length/2); //once the paddle hits tha ball, it returns to the central point of the display 
			
			
			
		}
		else if(-32-9-1+ball.y0<sposta_y) sposta_y=-32-9-1+ball.y0;
			
		}
	
}
	else{

	if(ball.y0>MAX_Y-32-9-1){
		if(ball.y0+ball.dir_y*ball.shift_y>=MAX_Y-5){
	
		
			disable_timer(0);
		print_score2(Black);
		score[1]++;
		print_score2(White);
		if(score[1]==5){
			lose=1;
			
			GUI_Text((MAX_X-8*8)/2, MAX_Y-160+16,(uint8_t *) "You lose", Red, Black);	
			sprintf(stringa,"Score: %d",score[0]);
			GUI_Text( (MAX_X-8*7)/2,MAX_Y-160+18+16,(uint8_t *) stringa,Yellow, Black);
			GUI_Text2((MAX_X-10+8*8)/2, MAX_Y-160-2,(uint8_t *) "You win", Red, Black);
			sprintf(stringa,"Score: %d",score[1]);
			GUI_Text2( (MAX_X-10+8*8)/2,MAX_Y-160-2-18,(uint8_t *) stringa,Yellow, Black);
			GUI_Text( (MAX_X-10-21*8)/2+5,MAX_Y-160,(uint8_t *) "Press Int0 to Restart",White, Blue); 
			
			NVIC_ClearPendingIRQ(EINT0_IRQn);
			NVIC_ClearPendingIRQ(EINT1_IRQn);
			NVIC_ClearPendingIRQ(EINT2_IRQn);
			NVIC_EnableIRQ(EINT0_IRQn);
			NVIC_SetPendingIRQ(EINT0_IRQn);
			NVIC_DisableIRQ(EINT1_IRQn);
			NVIC_DisableIRQ(EINT2_IRQn);
		}
		else {
			first=1;
			print_paddle(Black);
			print_ball(Black);
			init_paddle();
			print_paddle(Green);
			initball();
			print_ball(Green);
			enable_timer(0);
			
		}
		
			
			
		
		return;
		
	}
		if((ball.x0+4==x0-1 || ball.x0==x1+1) && (ball.y0<=MAX_Y-32)){
			dir=ball.dir_x;
			ball.dir_x=-dir;
			ball.shift_x=sposta_x=5+4;
			ball.shift_y=sposta_y=5;
			
		}
		if(-(ball.x0+ball.dir_x*(ball.shift_x+4))+x0<5  && -(ball.x0+ball.dir_x*(ball.shift_x+4))+x0>-14&&(ball.y0+ball.dir_y*ball.shift_y<=MAX_Y-32 || ball.y0+ball.dir_y*ball.shift_y+4<=MAX_Y-32)){
			sposta_x+=x0-(ball.x0+ball.dir_x*ball.shift_x+4)-1;
		}
		else if((ball.x0+ball.dir_x*(ball.shift_x))-x1<5 && (ball.x0+ball.dir_x*(ball.shift_x))-x1>-14&&(ball.y0+ball.dir_y*ball.shift_y<=MAX_Y-32 || ball.y0+ball.dir_y*ball.shift_y+4<=MAX_Y-32 )){
			sposta_x+=-x1+(ball.x0+ball.dir_x*ball.shift_x)-1;
		}
		
		for(i=0;i<5;i++){
		
		
		LCD_DrawLine(ball.x0+i,ball.y0,ball.x0+i,ball.y0+4,Black);
		LCD_DrawLine(ball.x0+ball.dir_x*sposta_x+i,ball.y0+ball.dir_y*sposta_y,ball.x0+ball.dir_x*sposta_x+i,ball.y0+ball.dir_y*sposta_y+4,Green);
	}
		if((ball.x0<=x1 && ball.x0>=x0) || (ball.x0+4*ball.dir_x<=x1 && ball.x0+4*ball.dir_x>=x0) && (ball.y0<=MAX_Y-32 || ball.y0+4<=MAX_Y-32) )
			print_paddle(Green);
		
		ball.x0+=ball.dir_x*sposta_x;
		ball.y0+=ball.dir_y*sposta_y;
		if(ball.x0+ball.shift_x*ball.dir_x<5 || ball.x0+ball.shift_x*ball.dir_x+4>MAX_X-5)
			ball.shift_y=MAX_Y-ball.y0;
		return;
		
	}
	
		if(ball.y0+4<MAX_Y-32-9){
	if((ball.y0+ball.dir_y*(ball.shift_y+4)>MAX_Y-32-9-5)&&(((ball.x0+ball.shift_x*ball.dir_x<=x1)&&(ball.x0+ball.shift_x*ball.dir_x>=x0))||((ball.x0<=x1)&&(ball.x0>=x0))|| ((ball.x0+4<=x1)&&(ball.x0+4>=x0))))
	{
		
		if(ball.y0+ball.dir_y*4==MAX_Y-32-9-1){
				init_timer(1,500);
				enable_timer(1);			
				ball.dir_y=-1;
				part_paddle(ball.x0,racchetta);
			if(ball.shift_y>=8)
				flag=2;
		
			
			
		}
		else if(MAX_Y-32-9-1-ball.y0-4<sposta_y) sposta_y=MAX_Y-32-9-1-ball.y0-4;
			
		}
	}
		
}
		
	if(ball.x0+(ball.shift_x+4)*ball.dir_x>=MAX_X-5-1){
		
		if(ball.x0+4*ball.dir_x==MAX_X-5-1){
			flag=2;
			ball.dir_x=-1;
			b=(ball.x0-5)/ball.shift_x;
			if(first==0){
			init_timer(1,freqs[0]);
			enable_timer(1);}
			else first=0;
			NVIC_ClearPendingIRQ(EINT0_IRQn);
			NVIC_ClearPendingIRQ(EINT1_IRQn);
			NVIC_ClearPendingIRQ(EINT2_IRQn);
			NVIC_DisableIRQ(EINT1_IRQn);
		}
		else sposta_x=(MAX_X-5-1-ball.x0-4);	
		

		
	}
	if(ball.x0+ball.shift_x*ball.dir_x<5){
		
		if(ball.x0==5){
			flag=2;
			b=(MAX_X-5-ball.x0)/ball.shift_x;
			ball.dir_x=+1;
			init_timer(1,freqs[0]);
			enable_timer(1);
		}
		else if(ball.x0-5<sposta_x) sposta_x=ball.x0-5;	
		
	}
	if(flag==2&&ball.dir_y==-1){ 
		
		a=(-(32+9+1)+ball.y0)/ball.shift_y; //passi in cui la pallina raggiungerà la linea su cui si trova il paddle2
		//number of ball's shifts to reach the line in which it is placed the paddle2
		//b contains the number of shifts to reach the extreme portion of the wall
		//if the ball hits the ball before hitting the paddle2, the bottom paddle doesn't make any movement 
		//if the difference between the point where the ball hits and the paddle is <=1/3* display's length then I will move
		//if the ball moves fastly (shift_y > ) the paddle will move
		
		if( a<=b||(ball.y0+ball.shift_y*b-32-9-1<=MAX_Y*1/3) || ball.shift_y>=8)
			spostamento_paddle(ball.x0+a*ball.shift_x*ball.dir_x);
		
	}
		
	
	
	
	

	for(i=0;i<5;i++){
		
		
		LCD_DrawLine(ball.x0+i,ball.y0,ball.x0+i,ball.y0+4,Black);
		LCD_DrawLine(ball.x0+ball.dir_x*sposta_x+i,ball.y0+ball.dir_y*sposta_y,ball.x0+ball.dir_x*sposta_x+i,ball.y0+ball.dir_y*sposta_y+4,Green);
	}


		if((ball.x0+4*ball.dir_x<=sizeof(score[0])*8+5+7) && (ball.x0+5>=5+7)&&((ball.y0>=MAX_Y-160 && ball.y0<=MAX_Y-160+16)||((ball.y0+5>=MAX_Y-160 && ball.y0+5<=MAX_Y-160+16))) )
			print_score1(White);
		if((ball.x0+4*ball.dir_x>=MAX_X-5-sizeof(score[1])*8-8-5) && (ball.x0+5<=MAX_X-5-8)&&((ball.y0>=MAX_Y-160 && ball.y0<=MAX_Y-160+16)||((ball.y0+5>=MAX_Y-160 && ball.y0+5<=MAX_Y-160+16))) )
			print_score2(White);
	
	
		

		ball.x0+=ball.dir_x*sposta_x;
		ball.y0+=ball.dir_y*sposta_y;
		
	
}
ball_t getBall(){
	return ball;
}


