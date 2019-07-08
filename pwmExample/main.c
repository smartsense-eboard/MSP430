#include <msp430.h> 
#include <msp430fr2433.h>
#include <stdint.h>
/**
 * main.c
 */

/**
 * pwm_output()
 * input:
 * - onTime: this is the pulse width on time it should be between 1000 us to 2000 us
 * output: void
 *  for the server protocol a pulse is expected every 20 ms
 *  the pulse width should go between 1000 us for 0 percent throttle
 *  and 2000 for full throttle
 */
void pwm_output(uint16_t onTime)
{
    WDTCTL = WDTPW + WDTHOLD; //Disable the Watchdog timer for our convenience.
    P1DIR |= BIT2; //Set pin 1.2 to the output direction.
    P1SEL1 |= BIT2; //Select pin 1.1 as our PWM output.
    TA0CCR0 = 20000; //Set the period in the Timer A0 Capture/Compare 0 register to 20 ms.
    TA0CCTL1 = OUTMOD_7;
    TA0CCR1 = onTime; //The period in microseconds that the power is ON. this is controlable and should be between 1000 us and 2000 us
    TA0CTL = TASSEL_2 + MC_1; //TASSEL_2 selects SMCLK as the clock source, and MC_1 tells it to count up to the value in TA0CCR0.
    __bis_SR_register(LPM0_bits); //Switch to low power mode 0.
}


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	pwm_output(1500);

	return 0;
}
