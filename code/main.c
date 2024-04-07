/**
  * @file 	main.c
  * @brief APP Source file.
  *
  * This file contains The Application of Distance Measuring
  *
  * @author [Mohamed Mabrouk]
  * @date [1 MAR 2024]
  *
  * @SWversion 1.0.0
  *
  * @remarks
  *    -Platform         : AVR
  *    -Peripherial      : Atmega32
  */
  /*==================================================================================================================================*/

/* ===================================================================================================
											      Includes
	===================================================================================================*/
#include"lcd.h"
#include"ultrasonic.h"
#include"common_macros.h"
/* ===================================================================================================
									             Main Project
   ===================================================================================================*/

int main(void)
{
    /* Enable interrupts */
    ENABLE_INTERRUPTS();

    /* Initialize variables and peripherals */
    uint16 Value = 0;
    Ultrasonic_init();
    LCD_init();
    LCD_displayString("Distance= ");

    for (;;)
    {
        /* Read distance value from ultrasonic sensor */
        LCD_moveCursor(0, 10);
        Value = Ultrasonic_readDistance();

        /* Display distance value on LCD */
        LCD_intgerToString(Value);
        LCD_displayString(" Cm  ");
    }


}
