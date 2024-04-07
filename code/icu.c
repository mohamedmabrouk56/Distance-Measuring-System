/**
 * @file 	icu.c
 * @brief ICU Source file.
 *
 * This file contains The Implementation of Functions of the ICU module
 *
 * @author [Mohamed Mabrouk]
 * @date [22 FEB 2024]
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
#include"timer.h"
#include"gpio.h"
#include"common_macros.h"

/* ===================================================================================================
									    Global Variables
   =================================================================================================== */
static volatile void (*ICU_PtrCallBack)(void) = NULL_PTR;
/* ===================================================================================================
										Function Definition
   =================================================================================================== */
/**
 *
 * This Function responsible for initialize the ICU driver.
 *
 * @param[in]  Config_Ptr Type ICU_ConfigType
 * @param[out] none
 * @return none
 */
void ICU_init(const ICU_ConfigType* Config_Ptr)
{
	/* Configure ICP1 as input */
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);

	/* Timer 1 always operates in Normal Mode  */
	TCCR1A=0x0C;

	/* Choose the required clock value in the first three bits (CS10, CS11 and CS12) */
	TCCR1B=(TCCR1B & 0xF8) | ((Config_Ptr->ICU_Clock) & 0x07);

	/* Choose the required Edge */
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->ICU_Edge) << ICES1);

	/* Initial Value for Timer1 */
	TCNT1=0;

	/* Initial Value for Timer1 */
	ICR1=0;

	TIMSK |= (1<<TOCIE1);
}

void ICU_setCallBack(void(*a_ptr)(void))
{
	ICU_PtrCallBack=a_ptr;
}

/**
 *
 * This Function responsible for initialize the ICU driver.
 *
 * @param[in]  edgeType Type ICU_EdgeType
 * @param[out] none
 * @return none
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType edgeType)
{
	TCCR1B = (TCCR1B & 0xBF) | (edgeType << ICES1);
}

/**
 *
 * This Function to get the Timer1 Value when the input is captured
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
uint16 ICU_getInputCaptureValue(void)
{
return ICR1;
}

/**
 *
 * This Function is to clear the Timer1 Value to start again from zero
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}


/**
 *
 * This Function responsible for Deinitialize the ICU driver.
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void ICU_deInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;
	ICR1   = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TOCIE1);

	/* Reset the Call Back Function */
	ICU_PtrCallBack = NULL_PTR;
}

void __vector_6(void) /* ICU ISR*/
{
	ICU_PtrCallBack();
}
