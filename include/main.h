/*******************************************************************************
  * @file    main.h
  * @author  Титков А.В.
  * @version v0.0.0.1
  * @date    09.11.2022
  *****************************************************************************/
#ifndef MAINH
#define MAINH


#define	START_BEGIN_ADDR		0x08000000 /* Start partition. Selects whether to jump to MAIN_APP or BOOTLOADER. Validates both*/
#define BOOT_BEGIN_ADDR			0x08020000
#define BOOT_END_ADDR			0x0803FFFB
#define MAIN_BEGIN_ADDR			0x08080000
#define MAIN_END_ADDR			0x080FFFFB	
	
#endif
