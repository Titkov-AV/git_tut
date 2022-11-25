/******************************************************************************
  * @file    stm32f4xx_it.c
  * @author  Пискунов С.Н.
  * @version v0.0.0.1
  * @date    08.02.2016
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "main.h"

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
	while (1);
}

void MemManage_Handler(void)
{
	while (1);
}

void BusFault_Handler(void)
{
	while (1);
}

void UsageFault_Handler(void)
{
	while (1);
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}

void EXTI15_10_IRQHandler(void)
{
}

void ETH_IRQHandler(void)
{
}

void EXTI9_5_IRQHandler(void)
{
}
