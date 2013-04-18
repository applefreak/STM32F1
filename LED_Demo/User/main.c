/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void GPIOA_Init(void);
void Delay(uint32_t nCount);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	GPIOA_Init();
	
	while(1) {
	GPIO_SetBits(GPIOB , GPIO_Pin_0);
	Delay(0xFFFFF);
	GPIO_ResetBits(GPIOB , GPIO_Pin_0);
	Delay(0xFFFFF);
	}
}

void GPIOA_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure; //定義資料形態
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //啟用APB2 Peripheral的clock

	/*以下為GPIO參數設定*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0; //設定Pin_0也就是GPIOA的P0
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; //設定為輸出push-pul	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度為50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始
}

void Delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
