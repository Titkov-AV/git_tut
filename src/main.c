/******************************************************************************
  * @file    main.c
  * @author  titav
  * @version v0.0.0.1
  * @date    09.11.2022
  * @brief   CRC32 project test
******************************************************************************/

#include <string.h>

#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_crc.h" 
#include "utils.h"

/* Определяем ножки Switch */
#define PORT_PIN0		GPIOB
#define GPIO_PIN0		GPIO_Pin_4
#define PORT_PIN1		GPIOB
#define GPIO_PIN1		GPIO_Pin_5
#define PORT_PIN2		GPIOB
#define GPIO_PIN2		GPIO_Pin_6
#define PORT_PIN3		GPIOB
#define GPIO_PIN3		GPIO_Pin_7

static uint32_t calcCrc32(uint32_t *data, uint32_t len)
{
	uint32_t *pBuffer = data;
	uint32_t BufferLength = len / 4;
	uint32_t index = 0;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	CRC_ResetDR();

	for(index = 0; index < BufferLength; index++) {
		CRC->DR = pBuffer[index];
	}

	return CRC->DR;
}

static int8_t crc_check(uint32_t start_addr, uint32_t end_addr)
{
	uint32_t size = (end_addr - start_addr + 4);
	uint32_t crc_value = calcCrc32((uint32_t*)start_addr, size);
	uint32_t crc_check = *((uint32_t*)(end_addr + 1));
	return (crc_value == crc_check) ? 1 : 0;
}

/// Передача адреса в R0
//\ param addr - преобразуемый адрес
static unsigned int *sys_addr(unsigned int *addr)
{
	return addr;
}

/// Переход по заданному адресу
//\ param addr - абсолютный адрес перехода
static void sys_goto(unsigned int addr)
{
	unsigned int *pload = (unsigned int*)addr;
	__set_MSP(*pload);
	sys_addr((unsigned int*)(addr+4));
	asm("ldr.w r14,[r0]");
	asm("movs r0, r14");
	asm("bx r0");
}

/// Основная точка входа
int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_PIN0, &GPIO_InitStructure);
	GPIO_Init(PORT_PIN1, &GPIO_InitStructure);
	GPIO_Init(PORT_PIN2, &GPIO_InitStructure);
	GPIO_Init(PORT_PIN3, &GPIO_InitStructure);

	uint8_t oktet = 0;
	if (!(PORT_PIN0->IDR & GPIO_PIN0)) mSetBit(oktet, 0);
	if (!(PORT_PIN1->IDR & GPIO_PIN1)) mSetBit(oktet, 1);
	if (!(PORT_PIN2->IDR & GPIO_PIN2)) mSetBit(oktet, 2);
	if (!(PORT_PIN3->IDR & GPIO_PIN3)) mSetBit(oktet, 3);
	
	if (oktet == 1) {
boot:	if(crc_check(BOOT_BEGIN_ADDR, BOOT_END_ADDR)) {
			sys_goto(BOOT_BEGIN_ADDR);
		} else {
			/* обе лампочки красные */
			while(1);
		}
	} else {
		if (crc_check(MAIN_BEGIN_ADDR, MAIN_END_ADDR)) {
			sys_goto(MAIN_BEGIN_ADDR);
		} else {
			goto boot;
		}
	}
}
