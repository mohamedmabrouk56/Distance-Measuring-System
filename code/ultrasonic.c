/**
 * @file 	ultrasonic.c
 * @brief Ultrasonic Source file.
 *
 * This file contains The Implementation of Functions of the Ultrasonic module
  *
  * @author [Mohamed Mabrouk]
  * @date [3 MAR 2024]
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
#include"icu.h"
#include"ultrasonic.h"
#include"gpio.h"
#include"util/delay.h"

uint8 edgeCount = 0;
uint16 T = 0;
/* ===================================================================================================
										  Function Definition
   ===================================================================================================*/
void Ultrasonic_init(void)
{
ICU_init(&ICU_Configuration);

ICU_setCallBack(Ultrasonic_edgeProcessing);

GPIO_setupPinDirection(ULTRASONIC_TR_PORT_ID, ULTRASONIC_TR_PIN_ID, PIN_OUTPUT);
}

static void Ultrasonic_Trigger(void)
{
GPIO_writePin(ULTRASONIC_TR_PORT_ID, ULTRASONIC_TR_PIN_ID, LOGIC_HIGH);
_delay_us(10);
GPIO_writePin(ULTRASONIC_TR_PORT_ID, ULTRASONIC_TR_PIN_ID, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void)
{
	uint16  distance  = 0;
	edgeCount = 0;
	T  = 0;

	Ultrasonic_Trigger();

	while(edgeCount < ULTRASONIC_PERIOD_NUM_EDGES);

	distance =((float32)T/58)+1;

	return distance;
}

void Ultrasonic_edgeProcessing(void)
{
		edgeCount++;
		if (edgeCount == 1)
		{
			ICU_clearTimerValue();
			ICU_setEdgeDetectionType(FALLING_EDGE);
		}
		else if (edgeCount == 2)
		{
		  T = ICU_getInputCaptureValue();

			ICU_setEdgeDetectionType(RISING_EDGE);
		}
}
