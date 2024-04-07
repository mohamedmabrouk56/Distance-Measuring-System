/**
  * @file ultrasonic.h
  * @brief Header file for the Ultrasonic module.
  *
  * This file contains the declarations and definitions for the Ultrasonic module
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
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

 /* ===================================================================================================
											  Includes
	===================================================================================================*/
#include"Std_Types.h"
#include"ultrasonic_Cfg.h"

#define ULTRASONIC_PERIOD_NUM_EDGES 2
/* ===================================================================================================
									   Function Prototypes
   ===================================================================================================*/
void Ultrasonic_init(void);

static void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
