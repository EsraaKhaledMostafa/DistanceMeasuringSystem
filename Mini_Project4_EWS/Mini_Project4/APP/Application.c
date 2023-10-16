/*
 *  Module: main
 *  File Name: application.c
 *  Description: Application for interfacing temp sensor and ADc with atmega32
 *  Author: Esraa Khaled
 */

#include "../HAL/lcd.h"
#include "../HAL/ultrasonic.h"
#include "../LIB/atmega32_registers.h"

int main(void)
{
	/*Variable to store the distance calculated by the ultrasonic sensor*/
	uint16 distance = 0;

	/*Enable the global interrupts*/
	SREG.bits.I_BIT = 1;

	/*Initialize the LCD and Ultrasonic Drivers*/
	LCD_init();
	Ultrasonic_init();

	/*Display this string once*/
	LCD_displayString("Distance = ");
	while(1)
	{
		/*store the value of the distance*/
		distance = Ultrasonic_readDistance();

		/* Display the distance value every time at same position */
		if(distance > 100)
		{
			LCD_moveCursor(0,11);
			LCD_integerToString(distance);
		}
		else
		{
			LCD_moveCursor(0,11);
			LCD_integerToString(distance);
			/* In case the digital value is one or two digits print spaces in the next digit place */
			LCD_displayString(" ");
		}
		LCD_displayStringRowColumn(0,14,"cm");
	}
}


