/**
  * @file timer.h
  * @brief Header file for the TIMER module.
  *
  * This file contains the declarations and definitions for the TIMER module
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

#ifndef TIMER_H_
#define TIMER_H_
/* ===================================================================================================
										   Includes
   ===================================================================================================*/
#include"Std_Types.h"
#include"timer_Cfg.h"
#include"timer_Regs.h"
/* ===================================================================================================
										Types Declaration
   ===================================================================================================*/

typedef enum
{
	TIMER0,
	TIMER1,
	TIMER2
}Timer_ID;

typedef enum
{
	/*Timer 0*/
	TIMER0_NO_SOURCE=0,
	TIMER0_NO_PRESCALER,
	TIMER0_PRESCALER_8,
	TIMER0_PRESCALER_64,
	TIMER0_PRESCALER_256,
	TIMER0_PRESCALER_1024,
	TIMER0_EXTSOURCE_FALLING,
	TIMER0_EXTSOURCE_RISING,

	/*Timer 1*/
	TIMER1_NO_SOURCE=0,
	TIMER1_NO_PRESCALER,
	TIMER1_PRESCALER_8,
	TIMER1_PRESCALER_64,
	TIMER1_PRESCALER_256,
	TIMER1_PRESCALER_1024,
	TIMER1_EXTSOURCE_FALLING,
	TIMER1_EXTSOURCE_RISING,

	/*Timer 2*/
	TIMER2_NO_SOURCE=0,
	TIMER2_NO_PRESCALER,
	TIMER2_PRESCALER_8,
	TIMER2_PRESCALER_32,
	TIMER2_PRESCALER_64,
	TIMER2_PRESCALER_128,
	TIMER2_PRESCALER_256,
	TIMER2_PRESCALER_1024,

}TIMER_Prescaler;

typedef enum
{
TIMER0_OVF = 0 ,
TIMER0_PHASE_PWM ,
TIMER0_CTC ,
TIMER0_FAST_PWM ,

TIMER1_OVF = 0,
TIMER1_PHASE_PWM_8BIT   ,
TIMER1_PHASE_PWM_9BIT   ,
TIMER1_PHASE_PWM_10BIT  ,
TIMER1_CTC_OCR 			,
TIMER1_FAST_PWM_8BIT    ,
TIMER1_FAST_PWM_9BIT    ,
TIMER1_FAST_PWM_10BIT	,
TIMER1_CTC_ICR = 12     ,
TIMER1_FAST_PWM_ICR	= 14,
TIMER1_FAST_PWM_OCR ,

TIMER2_OVF = 0 ,
TIMER2_PHASE_PWM ,
TIMER2_CTC ,
TIMER2_FAST_PWM
}Timer_Modes;

typedef enum
{
FAST_PWM_DISCONNECTED,
FAST_PWM_NON_INVERTING,
FAST_PWM_INVERTING
}Timer_Pwm_Mode;

typedef enum
{
OC_DISCONNECTED ,
OC_TOOGLE ,
OC_CLEAR  ,
OC_SET
}Timer_CTC_Mode;

typedef struct
{
	Timer_ID 			TimerNum;
	TIMER_Prescaler 	Prescaler;
	Timer_Modes			Mode;
	Timer_Pwm_Mode		PwmMode;
	Timer_CTC_Mode		CtcMode;
}TIMER_UnitConfig;

typedef struct
{
	const TIMER_UnitConfig* Units;
}TIMER_ConfigType;

extern const TIMER_ConfigType TIMER_Configuration;
/* ===================================================================================================
									   Function Prototypes
   ===================================================================================================*/

/**
 *
 * This Function responsible for initialize the TIMER driver.
 *
 * @param[in]  Config_Ptr Type TIMER_ConfigType
 * @param[out] none
 * @return none
 */
void TIMER_init(const TIMER_ConfigType *Config_Ptr);

uint8 TIMER_read(Timer_ID Timer_num);

void TIMER_setPreloadValue (Timer_ID Timer_num,uint16 Preload);

void TIMER_setCompareMatch (Timer_ID Timer_num, uint16 Value);

void TIMER_setCallBack(Timer_ID Timer_num , void (*copy_ptr)(void));

void TIMER0_setPwmDutyCycle (uint8 DutyCycle);

void TIMER1_setPwmDutyCycle (uint8 DutyCycle,uint8 Circuit);

void TIMER2_setPwmDutyCycle (uint8 DutyCycle);

/*ISR*/

void __vector_4(void)     __attribute__((signal)); /*TIMER2 COMP ISR*/

void __vector_5(void)     __attribute__((signal)); /*TIMER2 OVF ISR*/

void __vector_7(void)     __attribute__((signal)); /*TIMER1 COMPA ISR*/

void __vector_8(void)     __attribute__((signal)); /*TIMER1 COMPB ISR*/

void __vector_9(void)     __attribute__((signal)); /*TIMER1 OVF ISR*/

void __vector_10(void)    __attribute__((signal)); /*TIMER0 COMP ISR*/

void __vector_11(void)    __attribute__((signal)); /*TIMER0 OVF ISR*/

#endif /* TIMER_H_ */
