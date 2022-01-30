#include "GLCD/GLCD.h"
#include "GLCD/AsciiLib.h"
#include "timer/timer.h"
#define LENGTH 10



typedef struct{
	int x0;
	int length; 
	int dir;
	
}racchetta_t;
typedef struct{
	int x0;
	int y0;
	int dir_x;
	int dir_y;
	int shift_x;
	int shift_y;
}ball_t;

typedef struct{
	
	int dx;
	int sx;
	
	}sposta_paddle_t;

void init_paddle(void);
void initball(void);
void start_game(void);
void print_paddle(uint16_t Color);
void print_paddle1(uint16_t Color);
void print_paddle2(uint16_t Color);
void move_paddle1(int shift);
void move_paddle2(int shift);
void print_ball(uint16_t Color);
void print_score1(uint16_t Color);
void print_score2(uint16_t Color);
void move_ball(void);
void init_movement(void);
racchetta_t getRacchetta1(void);
racchetta_t getRacchetta2(void);
ball_t getBall(void);
void spostamento_paddle(int position);
sposta_paddle_t getSposta(void);

