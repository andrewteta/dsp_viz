/*
 * -------------------------------------------
 *    MSP432 DriverLib - v3_21_00_05 
 * -------------------------------------------
 *
 * --COPYRIGHT--,BSD,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*******************************************************************************
 * MSP432 ADC14 -  Single Channel with External Reference
 *
 * Description: This very simple code example shows the use of an external
 * reference for use in the ADC14 module. A single channel sample/conversion
 * is setup on input A0 (P5.5) and the sample timer is used to continuously
 * store the result in a local variable. The value coming in VREF+ (P5.6) is
 * treated as the max value of the ADC and the value coming in VREF- (P5.7) is
 * treated as the minimum value.
 *
 *                MSP432P401
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST         P5.5  |<---- A0 In
 *            |            P5.6  |<---- VREF+
 *            |            P5.7  |<---- VREF-
 *            |                  |
 *
 * Author: Timothy Logan
 ******************************************************************************/
/* DriverLib Includes */
#include "driverlib.h"

#include "periph_config.h"

/* Standard Includes */
#include <stdint.h>

#include <string.h>

#define TEST_LENGTH_SAMPLES 1024
#define SAMPLE_LENGTH 1024

/* ------------------------------------------------------------------
* Global variables for FFT Bin Example
* ------------------------------------------------------------------- */
uint32_t fftSize = SAMPLE_LENGTH;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
volatile arm_status status;
volatile uint16_t adcResult;

int main(void)
{
    /* Halting WDT and disabling master interrupts */
    WDT_A_holdTimer();
    Interrupt_disableMaster();

    configureClocks();
    configureGPIO();
    configureADC();
    //configureUART();

    Interrupt_enableSleepOnIsrExit();

    /* Enabling Interrupts */
    Interrupt_enableInterrupt(INT_ADC14);
    Interrupt_enableMaster();

    /* Triggering the start of the sample */
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();

    /* FFT data/processing buffers*/
    float hann[SAMPLE_LENGTH];
    int16_t data_array1[SAMPLE_LENGTH];
    int16_t data_array2[SAMPLE_LENGTH];
    int16_t data_input[SAMPLE_LENGTH*2];
    int16_t data_output[SAMPLE_LENGTH];

    // Initialize Hann Window
    int n;
    for (n = 0; n < SAMPLE_LENGTH; n++)
    {
        hann[n] = 0.5 - 0.5 * cosf((2*PI*n)/(SAMPLE_LENGTH-1));
    }

    /* Going to sleep */
    while (1)
    {
        PCM_gotoLPM0();

        //Fourier transform data and UART

        int i = 0;

        /* Computer real FFT using the completed data buffer */
        if (switch_data & 1)
        {
            for (i=0; i<SAMPLE_LENGTH; i++)
            {
                data_array1[i] = (int16_t)(hann[i]*data_array1[i]);
            }
            arm_rfft_instance_q15 instance;
            status = arm_rfft_init_q15(&instance, fftSize, ifftFlag, doBitReverse);

            arm_rfft_q15(&instance, data_array1, data_input);
        }
        else
        {
            for (i=0; i<SAMPLE_LENGTH; i++)
            {
                data_array2[i] = (int16_t)(hann[i]*data_array2[i]);
            }
            arm_rfft_instance_q15 instance;
            status = arm_rfft_init_q15(&instance, fftSize, ifftFlag, doBitReverse);

            arm_rfft_q15(&instance, data_array2, data_input);
        }

        /* Calculate magnitude of FFT complex output */
        for (i = 0; i < 2*SAMPLE_LENGTH; i+=2)
        {
            data_output[i/2] = (int32_t)(sqrtf((data_input[i] * data_input[i]) + (data_input[i+1] * data_input[i+1])));
        }

        q15_t maxValue;
        uint32_t maxIndex = 0;

        arm_max_q15(data_output, fftSize, &maxValue, &maxIndex);

    }
}

/* This interrupt happens whenever a conversion has been completed and placed
 * into ADC_MEM0. */
void ADC14_IRQHandler(void)
{
    uint64_t status;

    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);

    if(status & ADC_INT0)
    {
        adcResult = ADC14_getResult(ADC_MEM0);
    }

}
