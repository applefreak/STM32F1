#include "stm32f10x.h"
#include "comFunc.h"
#include "hd44780.h"

#define LCD_Port GPIOA
#define RS GPIO_Pin_0
#define EN GPIO_Pin_1
#define D4 GPIO_Pin_2
#define D5 GPIO_Pin_3
#define D6 GPIO_Pin_4
#define D7 GPIO_Pin_5

void strobeEN(void);
void upNib(uint8_t c);
void downNib(uint8_t c);

void lcdInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	//Init GPIOs
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = EN | RS | D4 | D5 | D6 | D7; 
	GPIO_ResetBits(LCD_Port, EN | RS | D4 | D5 | D6 | D7);
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LCD_Port, &GPIO_InitStructure);
	GPIO_ResetBits(LCD_Port, EN | RS | D4 | D5 | D6 | D7);
	
	//LCD 4 bit Init
	GPIO_SetBits(LCD_Port, D5);
	strobeEN();
	GPIO_ResetBits(LCD_Port, D5);
	sendCMD(0x28);
	sendCMD(0x0e);
	sendCMD(0x1);
	sendCMD(0x6);
}

void strobeEN(void) {
	Delay(0xfff);
	GPIO_SetBits(LCD_Port, EN);
	Delay(0xffff);
	GPIO_ResetBits(LCD_Port, EN);
}

void upNib(uint8_t c) {
	if(c & 0x80)
		GPIO_SetBits(LCD_Port, D7);
	else
		GPIO_ResetBits(LCD_Port, D7);
	if(c & 0x40)
		GPIO_SetBits(LCD_Port, D6);
	else
		GPIO_ResetBits(LCD_Port, D6);
	if(c & 0x20)
		GPIO_SetBits(LCD_Port, D5);
	else
		GPIO_ResetBits(LCD_Port, D5);
	if(c & 0x10)
		GPIO_SetBits(LCD_Port, D4);
	else
		GPIO_ResetBits(LCD_Port, D4);
}

void downNib(uint8_t c) {
	if(c & 0x8)
		GPIO_SetBits(LCD_Port, D7);
	else
		GPIO_ResetBits(LCD_Port, D7);
	if(c & 0x4)
		GPIO_SetBits(LCD_Port, D6);
	else
		GPIO_ResetBits(LCD_Port, D6);
	if(c & 0x2)
		GPIO_SetBits(LCD_Port, D5);
	else
		GPIO_ResetBits(LCD_Port, D5);
	if(c & 0x1)
		GPIO_SetBits(LCD_Port, D4);
	else
		GPIO_ResetBits(LCD_Port, D4);
}

void sendCMD(uint8_t c) {
	upNib(c);
	strobeEN();
	downNib(c);
	strobeEN();
}

void printChar(uint8_t c) {
	GPIO_SetBits(LCD_Port, RS);
	upNib(c);
	strobeEN();
	downNib(c);
	strobeEN();
	GPIO_ResetBits(LCD_Port, RS);
}
