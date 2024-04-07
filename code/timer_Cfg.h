/**
 * @file 	timer_Cfg.h
 * @brief TIMER Configratuions Header File.
 *
 * This file contains the Configratuions for the TIMER module
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
#ifndef TIMER_CFG_H_
#define TIMER_CFG_H_

//#define  F_CPU 8000000UL					/*System Clock*/
#define NUMBER_OF_USED_TIMERS 3

#define TIMER0_MAX_COUNT 255
#define TIMER1_MAX_COUNT 65535
#define TIMER2_MAX_COUNT 255

#endif
