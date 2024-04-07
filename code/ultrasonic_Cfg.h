/**
 * @file 	ultrasonic_Cfg.h
 * @brief Ultrasonic Configratuions Header File.
 *
 * This file contains the Configratuions for the Ultrasonic module
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

#ifndef ULTRASONIC_CFG_H_
#define ULTRASONIC_CFG_H_

/* used pins & ports*/

/**
  * @brief Used Port for TR Pin in Ultrasonic
  *
  * @details
  * - Type: define
  * - Range: 3U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define ULTRASONIC_TR_PORT_ID PORTB_ID
/**
  * @brief Used Pin for TR in Ultrasonic
  *
  * @details
  * - Type: define
  * - Range: 4U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define ULTRASONIC_TR_PIN_ID PIN5_ID
/**
  * @brief Used Port for Echo Pin in Ultrasonic
  *
  * @details
  * - Type: define
  * - Range: 3U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define ULTRASONIC_ECHO_PORT_ID PORTD_ID
/**
  * @brief Used Pin for Echo in Ultrasonic
  *
  * @details
  * - Type: define
  * - Range: 5U
  * - Resolution: Fixed
  * - Unit: Bits
  */
#define ULTRASONIC_ECHO_PIN_ID PIN6_ID

#endif /* ULTRASONIC_CFG_H_ */
