/*
 *  Module: ICU
 *  File Name: icu.c
 *  Description: Source file for the ICU driver
 *  Author: Esraa Khaled
 */


#include "icu.h"
#include "../LIB/common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*Global Variables*/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*Interrupt Service Routines*/
ISR (TIMER1_CAPT_vect)
{
	/*Call the callback function using pointer to function on detecting the edge*/
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}


/*Functions Definitions*/

/*Initializing function of the ICU*/
void ICU_init(const ICU_ConfigType *Config_Ptr)
{
	/*Configure ICP1 at pin 6 in PORTD --> i/p */
	CLEAR_BIT(DDRD,PD6);

	/*Set initial value for Timer1 to start counting from*/
	TCNT1 = 0;

	/*Set initial value for input capture unit register*/
	ICR1 = 0;

	/*Configure Timer1 to always operate in Normal Mode*/
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);

	/*Configure the Clock value CS10, CS11, CS12*/
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr-> clock);

	/*Configure the required edge to be detected by the ICU*/
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge)<<ICES1);

	/*Enable ICU interrupt to generate interrupt on detecting the edge*/
	SET_BIT(TIMSK,TICIE1);
}

/*Function to set the edge needed to be detected*/
void ICU_setEdgeDetection (const ICU_EdgeType a_edge_type)
{
	/*Configure the required edge to be detected by the ICU*/
	TCCR1B = (TCCR1B & 0xBF) | (a_edge_type<<ICES1);
}

/*Function to get the value of Timer1 present in the ICU value register on detecting the edge*/
uint16 ICU_getTimerValue(void)
{
	return ICR1;
}

/*Function to clear the timer value present in the ICU register to start counting from zero*/
void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*Function to set the callback function address*/
void ICU_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

/*Function to disable Timer1 to stop the ICU*/
void ICU_deinit(void)
{
	/*Clear all ICU Timer1 registers*/
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/*Disable ICU Interrupt*/
	CLEAR_BIT(TIMSK,TICIE1);

	/*reset the global pointer to point to null*/
	g_callBackPtr = NULL_PTR;
}
