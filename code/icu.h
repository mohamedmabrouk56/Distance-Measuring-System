/**
 * @file 	icu.h
 * @brief ICU Header file.
 *
 * This file contains the declarations and definitions for the ICU module
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
#ifndef ICU_H_
#define ICU_H_

/* ===================================================================================================
										   Includes
   ===================================================================================================*/

#include"std_types.h"

/* ===================================================================================================
										Types Declaration
   ===================================================================================================*/

/**
 * @brief Enumeration for ICU Edge Type.
 *
 *
 * @details
 * - Type: enum
 * - Range: 0:1
 * - Resolution: 1U
 * - Unit: Bits
 */
typedef enum
{
	FALLING_EDGE,RISING_EDGE
}ICU_EdgeType;

/**
 * @brief Enumeration for ICU Clock Prescaler.
 *
 *
 * @details
 * - Type: enum
 * - Range: 0:7
 * - Resolution: 1U
 * - Unit: Bits
 */
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_ClockType;

typedef struct
{
	ICU_EdgeType 	ICU_Edge;
	ICU_ClockType 	ICU_Clock;
}ICU_ConfigType;

extern const ICU_ConfigType ICU_Configuration;
/* ===================================================================================================
									   Function Prototypes
   ===================================================================================================*/

/**
 *
 * This Function responsible for initialize the ICU driver.
 *
 * @param[in]  Config_Ptr Type ICU_ConfigType
 * @param[out] none
 * @return none
 */
void ICU_init(const ICU_ConfigType * Config_Ptr);

void ICU_setCallBack(void(*a_ptr)(void));

/**
 *
 * This Function responsible for initialize the ICU driver.
 *
 * @param[in]  edgeType Type ICU_EdgeType
 * @param[out] none
 * @return none
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType edgeType);

/**
 *
 * This Function to get the Timer1 Value when the input is captured
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
uint16 ICU_getInputCaptureValue(void);

/**
 *
 * This Function is to clear the Timer1 Value to start again from zero
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void ICU_clearTimerValue(void);

/**
 *
 * This Function responsible for Deinitialize the ICU driver.
 *
 * @param[in]  none
 * @param[out] none
 * @return none
 */
void ICU_deInit(void);

void __vector_6(void)     __attribute__((signal)); /* ICU ISR */

#endif
