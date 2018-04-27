/*
 * periph_config.c
 *
 *  Created on: Apr 25, 2018
 *      Author: Andrew Teta
 */

#include "driverlib.h"
#include "periph_config.h"

void configureClocks(void) {
    /* Set to Vcore1 */
    PCM_setCoreVoltageLevel(PCM_VCORE1);

    /* Set to use DCDC */
    PCM_setPowerState(PCM_AM_DCDC_VCORE1);

    /* Set wait state */
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);

    /* Initializes Clock System */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_128 );
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    return;
}

void configureGPIO(void) {
    /* Terminating all remaining pins to minimize power consumption. This is
        done by register accesses for simplicity and to minimize branching API
        calls */
    GPIO_setAsOutputPin(GPIO_PORT_P1, PIN_ALL16);
    GPIO_setAsOutputPin(GPIO_PORT_P2, PIN_ALL16);
    GPIO_setAsOutputPin(GPIO_PORT_PB, PIN_ALL16);
    GPIO_setAsOutputPin(GPIO_PORT_PC, PIN_ALL16);
    GPIO_setAsOutputPin(GPIO_PORT_PD, PIN_ALL16);
    GPIO_setAsOutputPin(GPIO_PORT_PE, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_PB, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_PC, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_PD, PIN_ALL16);
    GPIO_setOutputLowOnPin(GPIO_PORT_PE, PIN_ALL16);

    /* Setting up GPIO pins as analog inputs (and references) */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,
            GPIO_PIN7 | GPIO_PIN6 | GPIO_PIN5 | GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);

    return;
}

void configureADC(void) {
    /* Initializing ADC (HSMCLK/1/1), HSMCLK=375kHz */
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_HSMCLK, ADC_PREDIVIDER_4, ADC_DIVIDER_4,
            0); // sample clock set to 23.44kHz

    /* Configuring ADC Memory (ADC_MEM0 A0/A1) in repeat mode
     * with use of external references */
    ADC14_configureSingleSampleMode(ADC_MEM0, true);
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_EXTPOS_VREFNEG_EXTNEG,
            ADC_INPUT_A0, false);



    /* Enabling sample timer in auto iteration mode and interrupts*/
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
    ADC14_enableInterrupt(ADC_INT0);
}


