#include "stm32f10x.h"
#include "comFunc.h"

#define outPort GPIOA
#define serialOUT GPIO_Pin_0
#define clk GPIO_Pin_1

void strobeCLK(void);
void dataOUT(uint8_t d);

void SIPO_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	//Init GPIOs
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = serialOUT | clk; 
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(outPort, &GPIO_InitStructure);
	GPIO_ResetBits(outPort, serialOUT | clk);
	dataOUT(0x0);
}

void dataOUT(uint8_t d) {
	uint8_t i;
	Delay(0xff);
	for(i=0x80;i>=1;i/=2) {
		if(d & i)
			GPIO_SetBits(outPort, serialOUT);
		else
			GPIO_ResetBits(outPort, serialOUT);
		strobeCLK();
	}
}

void strobeCLK(void) {
	Delay(0xf);
	GPIO_SetBits(outPort, clk);
	Delay(0xf);
	GPIO_ResetBits(outPort, clk);
}
