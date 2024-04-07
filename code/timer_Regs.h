/**
 * @file timer_Regs.h
 * @brief Header file for the TIMER Registers.
 *
 * This file contains the Registers for the TIMER module
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
#ifndef TIMER_REGS_H_
#define TIMER_REGS_H_
/* ===================================================================================================
											  Includes
   ===================================================================================================*/
#include "Std_Types.h"
/* ===================================================================================================
		   								   Timer Registers
   ===================================================================================================*/
   /* Control Registers*/
#define TCCR0    *((volatile uint8* const)(0x53))
#define TCCR1A   *((volatile uint8* const)(0x4F))
#define TCCR1B   *((volatile uint8* const)(0x4E))
#define TCCR2    *((volatile uint8* const)(0x45))
/*************************************************************************************************************/
	   /* Overflow Registers*/
#define TCNT0    *((volatile uint8* const)(0x52))
#define TCNT1H   *((volatile uint8* const)(0x4D))
#define TCNT1L   *((volatile uint8* const)(0x4C))
#define TCNT1   *((volatile uint16* const)(0x4C))
#define TCNT2    *((volatile uint8* const)(0x44))
/*************************************************************************************************************/
	   /* Compare Match Registers*/
#define OCR0     *((volatile uint8* const)(0x5C))
#define OCR1AH   *((volatile uint8* const)(0x4B))
#define OCR1AL   *((volatile uint8* const)(0x4A))
#define OCR1A   *((volatile uint16* const)(0x4A))
#define OCR1BH   *((volatile uint8* const)(0x49))
#define OCR1BL   *((volatile uint8* const)(0x48))
#define OCR1B   *((volatile uint16* const)(0x48))
#define OCR2     *((volatile uint8* const)(0x43))
/*************************************************************************************************************/
	   /* Input Capture Register*/
#define ICR1H   *((volatile uint8* const)(0x47))
#define ICR1L   *((volatile uint8* const)(0x46))
#define ICR1   *((volatile uint16* const)(0x46))
/*************************************************************************************************************/
		/* Interrupts Mask Register*/
#define TIMSK   *((volatile uint8* const)(0x59))
		/* Interrupts Flag Register*/
#define TIFR    *((volatile uint8* const)(0x58))

#ifndef SREG
#define SREG   *((volatile uint8* const)(0x5F))
#define IBIT 7
#endif
/*************************************************************************************************************/
/*TCCR0*/
#define 		FOC0									7
#define 		WGM00									6
#define 		COM01									5
#define 		COM00									4
#define 		WGM01									3
#define 		CS02									2
#define 		CS01									1
#define 		CS00									0
/*************************************************************************************************************/
/*TCCR1A*/
#define 		COM1A1									7
#define 		COM1A0									6
#define 		COM1B1									5
#define 		COM1B0									4
#define 		FOC1A									3
#define 		FOC1B									2
#define 		WGM11									1
#define 		WGM10									0
/*************************************************************************************************************/
/*TCCR1B*/
#define 		ICNC1									7
#define 		ICES1									6
#define 		WGM13									4
#define 		WGM12									3
#define 		CS12									2
#define 		CS11									1
#define 		CS10									0
/*************************************************************************************************************/
/*TCCR2*/
#define 		FOC2									7
#define 		WGM20									6
#define 		COM21									5
#define 		COM20									4
#define 		WGM21									3
#define 		CS22									2
#define 		CS21									1
#define 		CS20									0
/*************************************************************************************************************/
/*TIMSK BITS*/
#define 		OCIE2									7
#define 		TOIE2									6
#define 		TOCIE1									5
#define 		OCIE1A									4
#define 		OCIE1B									3
#define 		TOIE1									2
#define 		OCIE0									1
#define 		TOIE0									0

/*************************************************************************************************************/
/*TIFR BITS*/
#define 		OCF2									7
#define 		TOV2									6
#define 		ICF1									5
#define 		OCF1A									4
#define 		OCF1B									3
#define 		TOV1									2
#define 		OCF0									1
#define 		TOVO									0

/**************************************************************************************************************/


#endif