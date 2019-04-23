/*!
@copyright

    Copyright (c) 2019, MinnowWare. All rights reserved.
    This program and the accompanying materials are licensed and made
    available under the terms and conditions of the BSD License
    which accompanies this distribution.  The full text of the license
    may be found at

    http://opensource.org/licenses/bsd-license.php

    THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
    WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

@file main.c

@brief
    This module implements the MinnowBlink182 main program
@todo
    - add command line parameter to control blink count and frequency

@mainpage
    MinnowBlink182 for MinnowBoard

@section intro_sec Introduction
    This program is used to blink the D2 LED on the MinnowBoard
    running the UEFI-Shell.


@subsection ref_sec References
    @note <a href="https://www.intel.com/content/www/us/en/embedded/products/bay-trail/atom-e3800-family-datasheet.html">https://www.intel.com/content/www/us/en/embedded/products/bay-trail/atom-e3800-family-datasheet.html</a>\n
    download BayTrail specification in external browser\n
    <a href="https://github.com/MinnowBoard-org/design-files/blob/master/minnowboard-turbot-dual-core/pcb-F400_R302_Turbot-B/Turbot_B_Dual_Core_F400_R302-SchematicRev200.pdf">https://github.com/MinnowBoard-org/design-files/blob/master/minnowboard-turbot-dual-core/pcb-F400_R302_Turbot-B/Turbot_B_Dual_Core_F400_R302-SchematicRev200.pdf</a>\n
    open link in external browser\n
    <a href="https://minnowboard.org/tutorials/blinking-the-d2-led">https://minnowboard.org/tutorials/blinking-the-d2-led</a>\n

    @subsection Parm_sec Command line parameters
    * none

*/
#include <stdio.h>
#include <time.h>
#define BLINKCOUNT 182

#define /*Gpio Dfx0 Pad Cfg           */gpio_dfx0           0x2170

int main(int argc, char** argv) {

    volatile int* pGPIO_D2_LED_CTRL;        //access 32 bit of GPIO
    unsigned gpiobase;                      // PCI 0/1F/0/4C[31:2]
    clock_t clk;
    int i;

    printf("Welcome, to the jungle\n");

    //
    // get the GPIO base from the LPC device 0/1F/0 register 0x4C
    //
    outpd(0xCF8, 0x80000000 + (0 << 16) + (0x1F << 11) + (0 << 8) + 0x4C);
    gpiobase = ~3 & inpd(0xCFC);

    pGPIO_D2_LED_CTRL = (void*)(gpiobase + gpio_dfx0 + 8 /* value offset */);

    for (i = BLINKCOUNT; i > -1 ; i--) {

        clk = CLOCKS_PER_SEC / 16 + clock();
        while (clk > clock())
            ;

        *pGPIO_D2_LED_CTRL ^= 1;
        printf("\b\b\b%3d", i);     // print remaining blinks
    }
    *pGPIO_D2_LED_CTRL = 0;         // LED ON when exit
}