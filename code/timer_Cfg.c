/*
 * @file timer_Cfg.c
 * @brief source file for the Timer module configuration.
 *
 * This file contains the declarations and definitions for the Timer module in accordance
 * with the AUTOSAR standard.
 *
 * @author [Mohamed Mabrouk]
 * @date [25 JAN 2024]
 *
 * @SWversion 1.0.0
 *
 * @remarks
 *    -Platform         : AVR
 *    -Peripherial      : Atmega32
 */
/*==================================================================================================================================*/
#include"timer.h"
#include"timer_Cfg.h"
/*====================================================================================*/

const TIMER_UnitConfig TIMER_Unit_Configuration [NUMBER_OF_USED_TIMERS] =
{
		{
				TIMER0,
				TIMER0_PRESCALER_256,
				TIMER0_CTC,
				FAST_PWM_NON_INVERTING,
				OC_DISCONNECTED

		},

		{
				TIMER1,
				TIMER1_NO_PRESCALER,
				TIMER1_CTC_OCR,
				FAST_PWM_NON_INVERTING,
				OC_DISCONNECTED
		},


		{
				TIMER2,
				TIMER2_PRESCALER_256,
				TIMER2_CTC,
				FAST_PWM_INVERTING,
				OC_DISCONNECTED
		},

};

const TIMER_ConfigType TIMER_Configuration =
{
		TIMER_Unit_Configuration
};
