/* Copyright (c) 2013 Nordic Semiconductor. All Rights Reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the license.txt file.
 */
/*
 * See README.md for a description of the application. 
 */ 
 
#include <stdbool.h>
#include "nrf51.h"
#include "nrf51_bitfields.h"
#include "nrf_gpio.h"
#include "boards.h"

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    nrf_gpio_range_cfg_output(LED_0, LED_1);
    nrf_gpio_pin_set(LED_0);
    
    NRF_CLOCK->TASKS_HFCLKSTART = 1;
    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0)
    {
    }
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    
    // Workaround for PAN item 11, nRF51822-PAN v2.0.pdf. Not needed on second revision chips. 
    NRF_POWER->TASKS_CONSTLAT = 1;
    
    NRF_GPIOTE->CONFIG[0] = GPIOTE_CONFIG_MODE_Task << GPIOTE_CONFIG_MODE_Pos |
                            GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos |
                            LED_1 << GPIOTE_CONFIG_PSEL_Pos | 
                            GPIOTE_CONFIG_OUTINIT_Low << GPIOTE_CONFIG_OUTINIT_Pos;
                            
    NRF_TIMER1->PRESCALER = 0;
    // Adjust the output frequency by adjusting the CC. 
    // Due to PAN item 33, you can't have this at 1 for first revision chips, and will hence be limited to 4 MHz. 
    NRF_TIMER1->CC[0] = 1;
    NRF_TIMER1->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos;
    NRF_TIMER1->TASKS_START = 1;
    
    NRF_PPI->CH[0].EEP = (uint32_t) &NRF_TIMER1->EVENTS_COMPARE[0];
    NRF_PPI->CH[0].TEP = (uint32_t) &NRF_GPIOTE->TASKS_OUT[0];
    
    NRF_PPI->CHENSET = PPI_CHENSET_CH0_Enabled << PPI_CHENSET_CH0_Pos;
    
    while (true)
    {
        
    }
}
/** @} */
