#include "LEDMatrix.h"

//private function prototype
void readArray(uint16_t j);

uint8_t cursor[64] = {0,0,1,0,0,1,0,0,
											0,1,0,1,1,0,1,0,
											1,0,0,0,0,0,0,1,
											1,0,0,0,0,0,0,1,
											1,0,0,0,0,0,0,1,
											0,1,0,0,0,0,1,0,
											0,0,1,0,0,1,0,0,
											0,0,0,1,1,0,0,0 };
uint16_t a=0;

void LEDMatrix_Init(void) { //
	//Timer NVIC Configs
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//Timer configs
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Period=12;
	TIM_TimeBaseStructure.TIM_Prescaler=9000;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	
	//GPIO Configs, there's 2 sets of GPIO that needs to config. One for "common" pins (line) for multiplex. The other set is for the output
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); /*使能LED灯使用的GPIO时钟*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//GPIO config for output, aka columns
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); /*使能LED灯使用的GPIO时钟*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_SetBits(GPIOC, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);


}

void line_select(uint8_t line) {
	switch(line) {
		case 0: GPIO_SetBits(GPIOB, GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
						GPIO_ResetBits(GPIOB, GPIO_Pin_8);
						readArray(0);
						break;
		case 1: GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
						GPIO_ResetBits(GPIOB, GPIO_Pin_9);
						readArray(8);
						break;
		case 2: GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
						GPIO_ResetBits(GPIOB, GPIO_Pin_10);
						readArray(16);
						break;
		case 3: GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
						GPIO_ResetBits(GPIOB,GPIO_Pin_11);
						readArray(24);
						break;
		case 4: GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
						GPIO_ResetBits(GPIOB,GPIO_Pin_12);
						readArray(32);
						break;
		case 5: GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15);
						GPIO_ResetBits(GPIOB,GPIO_Pin_13);
						readArray(40);
						break;
		case 6: GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15);
						GPIO_ResetBits(GPIOB,GPIO_Pin_14);
						readArray(48);
						break;
		case 7:	GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
						GPIO_ResetBits(GPIOB,GPIO_Pin_15);
						readArray(56);
						break;
		}						
}

void readArray(uint16_t j) {
	for(a=j;a<=(j+7);a++) {
		if(cursor[a]==1) {
			switch(a-j) {
				case 0: GPIO_ResetBits(GPIOC, GPIO_Pin_0); break;
				case 1: GPIO_ResetBits(GPIOC, GPIO_Pin_1); break;
				case 2: GPIO_ResetBits(GPIOC, GPIO_Pin_2); break;
				case 3: GPIO_ResetBits(GPIOC, GPIO_Pin_3); break;
				case 4: GPIO_ResetBits(GPIOC, GPIO_Pin_4); break;
				case 5: GPIO_ResetBits(GPIOC, GPIO_Pin_5); break;
				case 6: GPIO_ResetBits(GPIOC, GPIO_Pin_6); break;
				case 7: GPIO_ResetBits(GPIOC, GPIO_Pin_7); break;
			}
		}
			else {
				switch(a-j) {	
					case 0: GPIO_SetBits(GPIOC, GPIO_Pin_0); break;
					case 1: GPIO_SetBits(GPIOC, GPIO_Pin_1); break;
					case 2: GPIO_SetBits(GPIOC, GPIO_Pin_2); break;
					case 3: GPIO_SetBits(GPIOC, GPIO_Pin_3); break;
					case 4: GPIO_SetBits(GPIOC, GPIO_Pin_4); break;
					case 5: GPIO_SetBits(GPIOC, GPIO_Pin_5); break;
					case 6: GPIO_SetBits(GPIOC, GPIO_Pin_6); break;
					case 7: GPIO_SetBits(GPIOC, GPIO_Pin_7); break;
				}	
			}
		}								
}

/*
The Timer IRQ handler that's going to stm32f1x_it file, I'm putting it here for reference

void TIM2_IRQHandler(void) {
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET) {
		
		if(row==8) {
			row=0;
		}
		else {
			line_select(row);
			row++;
		}

		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
	}
}

*/
