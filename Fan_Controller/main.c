/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: main file to run the code
 *
 * Author: Omar Saad
 *
 *******************************************************************************/

#include "lcd.h"
#include "lm35_sensor.h"
#include "DcMotor.h"

int main(void)
{
	/* temp variable to store temperature from sensor */
	uint8 temp;

	/* initialize LCD driver */
	LCD_init();

	/* Display this string "Fan is " only once on LCD at the first row
	 * and  "Temp =   C" only once on LCD at the second row
	 */
	LCD_moveCursor(0,4);
	LCD_displayString("Fan is ");
	LCD_moveCursor(1,4);
	LCD_displayString("Temp =    C");

	/* Initialize DC Motor */
	DcMotor_Init();

	while(1)
	{

		/*  store the temperature value from LM35 sensor in temp variable*/
		temp = LM35_getTemperature();

		/* Display the temperature value every time at same position on LCD */
		LCD_moveCursor(1,11);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}


		/* Display the Motor State  every time at same position on LCD */
		/* Control Motor Fan speed based on temperature value */
		LCD_moveCursor(0,11);
		if (temp >= 120)
		{
			DcMotor_Rotate(CW,100);
			LCD_displayString("ON ");
		}
		else if (temp>=90)
		{
			DcMotor_Rotate(CW,75);
			LCD_displayString("ON ");
		}
		else if (temp>=60)
		{
			DcMotor_Rotate(CW,50);
			LCD_displayString("ON ");
		}
		else if (temp>=30)
		{
			DcMotor_Rotate(CW,25);
			LCD_displayString("ON ");
		}
		else
		{
			DcMotor_Rotate(STOP,0);
			LCD_displayString("OFF");
		}
	}
}
