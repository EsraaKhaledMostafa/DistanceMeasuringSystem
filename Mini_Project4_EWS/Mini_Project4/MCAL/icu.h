/*
 *  Module: ICU
 *  File Name: icu.h
 *  Description: Header file for the ICU driver
 *  Author: Esraa Khaled
 */

#ifndef ICU_H_
#define ICU_H_

#include "../LIB/std_types.h"

/*Types Declaration*/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256, F_CPU_1024
}ICU_ClockType;


typedef enum
{
	FALLING_EDGE, RISING_EDGE
}ICU_EdgeType;

typedef struct
{
	ICU_ClockType clock;
	ICU_EdgeType edge;
}ICU_ConfigType;


/*Functions Prototypes*/

/*Initializing function of the ICU*/
void ICU_init(const ICU_ConfigType *Config_Ptr);

/*Function to set the edge needed to be detected*/
void ICU_setEdgeDetection (const ICU_EdgeType a_edge_type);

/*Function to get the value of Timer1 present in the ICU value register on detecting the edge*/
uint16 ICU_getTimerValue(void);

/*Function to clear the timer value present in the ICU register to start counting from zero*/
void ICU_clearTimerValue(void);

/*Function to set the callback function address*/
void ICU_setCallBack(void(*a_ptr)(void));

/*Function to disable Timer1 to stop the ICU*/
void ICU_deinit(void);


#endif /* ICU_H_ */
