/*
 * @file icu_Cfg.c
 * @brief source file for the ICU module configuration.
 *
 * This file contains the declarations and definitions for the ICU module in accordance
 * with the AUTOSAR standard.
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
#include "icu.h"
/*====================================================================================*/
const ICU_ConfigType ICU_Configuration =
{
		RISING_EDGE,F_CPU_8
};
