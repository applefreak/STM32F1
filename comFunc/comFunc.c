#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32_eval.h"

/*Private Variables*/
	uint8_t i=0;
	uint8_t j=0;

/*******************************************************************************
* Function Name  : initToggle
* Description    : Initialize the toggle function.
* Input          : None
* Output         : None
* Return         : None
* Note           : The toggle pins are preset to PB10 & PB11
*******************************************************************************/
void initToggle(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); /*使能LED灯使用的GPIO时钟*/

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11; 
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : PB10Toggle
* Description    : Toggles LED on PB10.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PB10Toggle(void)
{
	if(i==0) {
		i++;
		GPIO_ResetBits(GPIOB, GPIO_Pin_10);
	}
	else {
		i=0;
		GPIO_SetBits(GPIOB, GPIO_Pin_10);
	}
}

/*******************************************************************************
* Function Name  : PB11Toggle
* Description    : Toggles LED on PB11.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PB11Toggle(void)
{
	if(j==0) {
		j++;
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);
	}
	else {
		j=0;
		GPIO_SetBits(GPIOB, GPIO_Pin_11);
	}
}
