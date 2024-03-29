/*  --------------------------------------------------------------------------
* Copyright 2016, Cypress Semiconductor Corporation.
*
* This software is owned by Cypress Semiconductor Corporation (Cypress)
* and is protected by and subject to worldwide patent protection (United
* States and foreign), United States copyright laws and international
* treaty provisions. Cypress hereby grants to licensee a personal,
* non-exclusive, non-transferable license to copy, use, modify, create
* derivative works of, and compile the Cypress Source Code and derivative
* works for the sole purpose of creating custom software in support of
* licensee product to be used only in conjunction with a Cypress integrated
* circuit as specified in the applicable agreement. Any reproduction,
* modification, translation, compilation, or representation of this
* software except as specified above is prohibited without the express
* written permission of Cypress.
* 
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND,EXPRESS OR IMPLIED,
* WITH REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising
* out of the application or use of any product or circuit described herein.
* Cypress does not authorize its products for use as critical components in
* life-support systems where a malfunction or failure may reasonably be
* expected to result in significant injury to the user. The inclusion of
* Cypress' product in a life-support systems application implies that the
* manufacturer assumes all risk of such use and in doing so indemnifies
* Cypress against all charges.
* 
* Use may be limited by and subject to the applicable Cypress software
* license agreement.
* -----------------------------------------------------------------------------
* Copyright (c) Cypress Semiconductors 2000-2016. All Rights Reserved.
*
*****************************************************************************
*  Project Name: Bootloadable2
*  Project Revision: 1.00
*  Software Version: PSoC Creator 3.3 SP2
*  Device Tested: CY8C3866AXI-040
*  Compilers Tested: Keil
*  Related Hardware: CY8CKIT-030
*****************************************************************************
***************************************************************************** */

/*
* Project Description:
* This is a sample bootloadable program demonstrating PSoC 5LP bootloading PSoC 3.
* The project is tested using two DVKs - One with PSoC 3 on CY8CKIT-030 and the second one
* with PSoC 5LP on CY8CKIT-050. PSoC 3 must be programmed with the UART_Bootloader Program and
* PSoC 5LP must be programmed with UART_Bootloader_Host program. The UART_Bootloader_Host program
* contains the *.cyacd file associated with the Bootloadable2 program. 
*
* The following events happen on each trigger of the button P6 [1] of CY8CKIT – 050 (PSoC 5LP):
*
* On first switch press, Bootloadable1.cyacd file will be bootloaded onto the target PSoC 3. 
* On successful bootloading the message “Bootloaded - Hello” will be displayed on the char LCD of  
* CY8CKIT – 050 and the message “Hello” will be displayed on the char LCD of CY8CKIT-030.
*
* For subsequent bootloading operation press the switch P6 [1] on CY8CKIT – 030. This makes PSoC 3 to enter bootloader 
* and be ready to bootload a new application.
*
* On next switch press on CY8CKIT – 050, Bootloadable2.cyacd file will be bootloaded onto the target PSoC 3. 
* On successful bootloading the message “Bootloaded - Bye” will be displayed on the char LCD of CY8CKIT – 050 LCD and the message “Bye” 
* will be displayed on the char LCD of CY8CKIT – 030.
***************************************************************************** */
#include <device.h>

int main()
{
    /* Initialize the char LCD and display "Bye" */
	LCD_Char_Start();
	LCD_Char_PrintString("Bye");
	
	/* Display the instruction to the user on how to start bootloading */
	LCD_Char_Position(1,0);
	LCD_Char_PrintString("SW1-P6.1 to BL");

	CYGlobalIntEnable;

    for(;;)
    {
        /* Jump to the Bootloader upon pressing the switch connected to the pin 'Pin_StartBootloader' */
		if(Pin_StartBootloader_Read() == 0)
		{
			/* Display the "Waiting to bootload" message */
			LCD_Char_Position(1,0);
			LCD_Char_PrintString("Waiting to BL  ");
			
			/* This API will pass the program control to the Bootloader portion of the flash.
			   It will also cause the Bootloader to wait indefinitely for the host to start communication */
			Bootloadable_Load();
		}        
    }
}

/* [] END OF FILE */
