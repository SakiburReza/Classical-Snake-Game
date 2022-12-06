/*
 * snake4ledinterface.c
 *
 * Created: 7/8/2021 4:37:33 PM
 * Author : Pavilion
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>
#include "LED.h"
#include <stdio.h>
#include <stdlib.h>

 

int dirX=1; // movement direction +x e move korle 1 -x e -1 x e move na korle  0 
int dirY=0;
int  snakelength =1;
int snakeloc[20][2]; 
int dir[20];
int snakedirtracker=0;
int changedir=0;
int curdir = 4;
int foodCol=7,foodRow=5;
int points=0;




int start_game = 1 ;
int end_game = 0;


void reset_lcd(){
	set_position(0,0);
	printf("               ");
	_delay_ms(20);
}

void lcd_msg(){
	if(start_game){
		start_game = 0 ;
		
		int tt=10;
		while(tt--){
		set_position(0, 0);
		printf("Welcome!");
		_delay_ms(200);
		}
		
		
		set_position(0, 0);
		printf("Score: %d", points);
		return ;
	}
	if (end_game){
		points = 0 ;
		start_game = 1 ;
		end_game = 0;
		_delay_ms(2000);
		reset_lcd();
		//lcd_msg();
	}
}

//
void uart_init()
{
	UCSRA = 0b00000010;
	UCSRB = 0b00011000;
	UCSRC = 0b10000110;
	
	UBRRH = 0;
	UBRRL = 12;
}


void uart_send(unsigned char data){
	while ((UCSRA & (1<<UDRE)) == 0x00);
	UDR = data;
}

unsigned char uart_receive(void){
	while ((UCSRA & (1<<RXC)) == 0x00);
	return UDR;
}

void set_position(int row, int col)
{
	uart_send(0xfe);
	uart_send(col + row * 64 + 128);
}

void show_char(char a)
{
	uart_send(a);
}




void foodGenerator(){
	foodCol= rand()%16;
	foodRow=rand()%16;
}

void updateDir(){
	int tmpx = dirX;
	int tmpy = dirY;
	
	int i=1;
	for (;i<snakelength;i++)
	{
		int tempx1 = snakeloc[i][0];
		int tempy1 =snakeloc[i][1];
		snakeloc[i][0]=tmpx;
		snakeloc[i][1] =tmpy;
		tmpx = tempx1; 
		tmpy = tempy1;
				
	}
}

void display(){
	int i=0;
	int t=50;
	while(t--){
	for (i=0;i<snakelength;i++)
	{
		ledPrintUsingTwoDecoder(snakeloc[i][1],snakeloc[i][0]);
		_delay_ms(2);
	}
	
	
	}
}

void resetGame(){
	set_position(0, 0);
	printf("Final Score : %d", points);
	points = 0 ;
	
	int kk=100;
	while (kk--)
	{
		//o
		ledPrintUsingTwoDecoder(2,1);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(3,1);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(4,1);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(1,2);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(1,3);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(1,4);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(1,5);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(2,6);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(3,6);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(4,6);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(5,2);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(5,3);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(5,4);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(5,5);
		_delay_ms(2);
		
		//V
		ledPrintUsingTwoDecoder(9,1);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(9,2);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(9,3);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(9,4);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(9,5);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(10,6);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(11,7);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(12,6);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(13,5);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(13,4);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(13,3);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(13,2);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(13,1);
		_delay_ms(2);
		//E
		ledPrintUsingTwoDecoder(1,9);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(1,10);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(1,11);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(1,12);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(1,13);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(1,14);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(1,15);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(2,9);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(3,9);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(4,9);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(2,12);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(3,12);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(2,15);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(3,15);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(4,15);
		_delay_ms(2);
		//R
		
		ledPrintUsingTwoDecoder(10,9);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(10,10);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(10,11);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(10,12);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(10,13);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(10,14);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(10,15);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(11,9);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(12,9);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(13,9);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(13,10);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(13,11);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(12,11);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(10,11);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(12,12);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(13,13);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(14,14);
		_delay_ms(2);
		ledPrintUsingTwoDecoder(15,15);
		_delay_ms(2);
		
		if(end_game==1) break;
		
		
	} 
	
	
	_delay_ms(50);
	
}

void showFood(){
	
	ledPrintUsingTwoDecoder(foodCol,foodRow);
	_delay_ms(1);
	
	if(foodCol == snakeloc[0][1] && foodRow == snakeloc[0][0]) {
		foodGenerator();
		set_position(0, 0);
		printf("Score: %d", ++points);
		snakelength++;
	}
	
}
int IsSnakeDead(){
	if(snakelength<5) return 0; // If length is lower than 5, snake cannot eat itself.
	unsigned char head[2]= { snakeloc[0][0] , snakeloc[0][1] };
	for(int i=4; i<snakelength; i++){
		if(head[0]==snakeloc[i][0]){
			if(head[1]==snakeloc[i][1]){
				return 1;
			}
		}
	}
	return 0;
}

 ISR(INT1_vect)
 {
	 int in = PINB;
	 if(in){
		 
		  if(in==16 ){
			  end_game = 1;
			  snakeloc[0][0]=4;
			  snakeloc[0][1]=5;
			  dirX=4;
			  dirY=4;
			  snakeloc[1][0]=4;
			  snakeloc[1][1]=4;
			  snakeloc[2][0]=4;
			  snakeloc[2][1]=3;
			  snakelength=3;
			  dir[0]=1;
			  curdir =4;
			  display();
		  }
		 if(in==1 && curdir !=1 && curdir!=4){//left
			 if(snakeloc[0][1]==0){
				 snakeloc[0][1] =15;
				 }else{
				 snakeloc[0][1]--;
			 }
			 updateDir();
			 dirX=snakeloc[0][0];
			 dirY = snakeloc[0][1];
			 curdir = 1;
		 }
		 if(in==2 && curdir!=2 && curdir!=8){//up
			 if(snakeloc[0][0]==0){
				 snakeloc[0][0] =15;
				 }else{
				 snakeloc[0][0]--;
			 }
			 updateDir();
			 dirX=snakeloc[0][0];
			 dirY = snakeloc[0][1];
			 curdir = 2;
		 }
		 if(in==4 && curdir !=1 &&curdir!=4 ){ //right
			 if(snakeloc[0][1]==15){
				 snakeloc[0][1]=0;
				 }else{
				 snakeloc[0][1] = ++snakeloc[0][1];
			 }
			 updateDir();
			 dirX=snakeloc[0][0];
			 dirY = snakeloc[0][1];
			 curdir =4;
		 }
		 if(in==8 && curdir!=2 && curdir!=8){//down
			 snakeloc[0][0] = (++snakeloc[0][0])%16;
			 updateDir();
			 dirX=snakeloc[0][0];
			 dirY = snakeloc[0][1];
			 curdir =8;
		 }
		
		 
		 
	 }
	 _delay_ms(20);
	 
 }


int main(void)
{

	DDRB = 0xFF;
	snakeloc[0][0]=4;
	snakeloc[0][1]=5;
	dirX=4;
	dirY=4;
	snakeloc[1][0]=4;
	snakeloc[1][1]=4;
	snakeloc[2][0]=4;
	snakeloc[2][1]=3;
	snakelength=3;
	dir[0]=1;
	curdir =4;
	
	uart_init();
	_delay_ms(10);
	stdout = fdevopen(uart_send, NULL);

	
	MCUCR = MCUCR | 0b00001100;
	GICR = 1<<INT1;
	sei();
	
	//resetGame();
	while (1)
	{
		lcd_msg();
		display();
		showFood();
		if(IsSnakeDead()){
			resetGame();
		}
		else{
		_delay_ms(10);
			if(curdir==1){//left
				if(snakeloc[0][1]==0){
					snakeloc[0][1] =15;
					}else{
					snakeloc[0][1]--;
				}
				updateDir();
				dirX=snakeloc[0][0];
				dirY = snakeloc[0][1];
				curdir = 1;
			}
			if(curdir==2){//up
				if(snakeloc[0][0]==0){
					snakeloc[0][0] =15;
				}else{
					snakeloc[0][0]--;
				}
				
				updateDir();
				dirX=snakeloc[0][0];
				dirY = snakeloc[0][1];
				curdir = 2;
			}
			if(curdir==4){ //right
				if(snakeloc[0][1]==15){
					snakeloc[0][1]=0;
					}else{
					snakeloc[0][1]++;
				}
				updateDir();
				dirX=snakeloc[0][0];
				dirY = snakeloc[0][1];
				curdir =4;
			}
			if(curdir==8){//down
				snakeloc[0][0] = (++snakeloc[0][0])%16;
				updateDir();
				dirX=snakeloc[0][0];
				dirY = snakeloc[0][1];
				curdir =8;
			}
			
		 
		
			}
			}
    
}

