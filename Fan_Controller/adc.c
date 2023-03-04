/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega32 ADC driver
 *
 * Author: Omar Saad
 *
 *******************************************************************************/
#include "adc.h"
#include "avr/io.h" /* To use the ADC Registers */
#include "common_macros.h" /* To use the macros*/

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 selected by ref_volt variable to select reference voltage
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */

	/*
	 * shift left ref_volt value by 6 to set value in last 2 bits (REFS1,REFS0) to select vref by user
	 */
	ADMUX = ((Config_Ptr->ref_volt)<<6) ;

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 selected by prescaler variable to choose ADC_Clock = F_CPU/128 = 16Mhz/128 = 125Khz --> ADC must operate in range 50-200Khz
	 */

	ADCSRA = (Config_Ptr->prescaler) ;

	ADCSRA = (1<<ADEN);
}

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num)
{
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x07);

	SET_BIT(ADCSRA,ADSC); //Start conversion

	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */

	SET_BIT(ADCSRA,ADIF); //Clear Flag

	return ADC; /* Read the digital value from the data register */

}
