/*
 * ultrasonic.h
 *
 *  Created on: Oct 15, 2023
 *      Author: DELL
 */

#ifndef HAL_ULTRASONIC_H_
#define HAL_ULTRASONIC_H_

#include "../LIB/std_types.h"

/*HW Interfacing Ports and Pins*/
#define TRIGGER_PORT      PORTB_ID
#define TRIGGER_PIN       PIN5_ID

#define ECHO_PORT         PORTD_ID
#define ECHO_PIN          PIN6_ID


/*Functions Prototypes*/

/*initialization Function of the Ultrasonic driver*/
 void Ultrasonic_init(void);

 /*Does the distance measurements and return with the distance*/
 uint16 Ultrasonic_readDistance(void);

 /*Call Back function*/
 void Ultrasonic_edgeProcessing(void);

#endif /* HAL_ULTRASONIC_H_ */
