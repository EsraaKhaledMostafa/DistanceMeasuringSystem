/*
 * ultrasonic.c
 *
 *  Created on: Oct 15, 2023
 *      Author: DELL
 */

#include "ultrasonic.h"
#include "../MCAL/icu.h"
#include "../MCAL/gpio.h"
#include <util/delay.h>

/*Global Variables*/
static volatile uint8 g_edgeCount = 0;
static uint16 timerValue = 0;

/*Private Functions*/

/*Send the trigger pulse to the ultrasonic*/
static void Ultrasonic_Trigger(void);

/*Functions Definitions*/

/*initialization Function of the Ultrasonic driver*/
 void Ultrasonic_init(void)
 {
	 /*Initialize the ICU driver as required*/
	 ICU_ConfigType ICU_Configurations = {F_CPU_8,RISING_EDGE};
	 ICU_init(&ICU_Configurations);

	 /*Setup the ICU call back function*/
	 ICU_setCallBack(Ultrasonic_edgeProcessing);

	 /*Setup the direction for the trigger pin as output pin through the GPIO driver*/
	 GPIO_setupPinDirection(TRIGGER_PORT,TRIGGER_PIN,PIN_OUTPUT);

 }


 /*Send the trigger pulse to the ultrasonic*/
 void Ultrasonic_Trigger(void)
 {
	 /*Send the Trigger pulse to the ultrasonic*/
	 GPIO_writePin(TRIGGER_PORT,TRIGGER_PIN,LOGIC_HIGH);

	 /*Duration of the pulse >= 10us*/
	 _delay_us(10);

	 /*lower the pulse*/
	 GPIO_writePin(TRIGGER_PORT,TRIGGER_PIN,LOGIC_LOW);
 }


 /*Does the distance measurements and return with the distance*/
  uint16 Ultrasonic_readDistance(void)
  {
	  uint16 distance = 0;

	  /*Send the trigger pulse by using Ultrasonic_Trigger function*/
	  Ultrasonic_Trigger();

	  /*Start the measurements by the ICU from this moment*/
	  while(g_edgeCount != 2);

	  g_edgeCount = 0;
	  /*ceiling the float distance value */
	  distance = 1 + (timerValue/58);

	  /*Sound velocity = 340.00 m/s = 34000 cm/s
	   The distance of Object (in cm) = 340000*Time / 2
		                               = 17000 * Time
		F_CPU = 8MHz and Prescaler = F_CPU/8 for timer frequency.
		Time to execute 1 instruction is 1 us.
		Distance = 17000 x (TIMER value) x 1 x 10^-6 cm
		         = 0.017 x (TIMER value) cm
		         = (TIMER value) / 58.8 cm*/

	  return distance;
  }


  /*Call Back function*/
  void Ultrasonic_edgeProcessing(void)
  {
	  /*increment the edges on every callback*/
	  g_edgeCount++;

	  if(g_edgeCount == 1)
	  {
		  /*start counting from detecting the first rising edge*/
		  ICU_clearTimerValue();
		  /*Configure ICU to detect the falling edge to know the echo period*/
		  ICU_setEdgeDetection(FALLING_EDGE);
	  }
	  else if(g_edgeCount == 2)
	  {
		  /*get the timer value of the echo period*/
		  timerValue = ICU_getTimerValue();
		  /*Reset the ICU to start measurements again*/
		  ICU_setEdgeDetection(RISING_EDGE);
		  ICU_clearTimerValue();
	  }
  }
