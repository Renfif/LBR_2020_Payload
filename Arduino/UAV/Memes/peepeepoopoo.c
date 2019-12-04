// IBT2 Library Example
//
// Ramps the IBT-2 output up from 0 to 100% forward, down to 100% reverse,
// and then back to 0 and repeats.
//
// The target is the FRDM-K64F board. You can hook up the EN lines directly to
// Vcc if you want to, but I have included them here for completeness.
//
// IBT-2 connections:
//   L_PWM -> PTC10
//   R_PWM -> PTC11
//   L_EN  -> PTB11
//   R_EN  -> PTB10 (or just wire to PTB11)
//   L_IS  -> not used
//   R_IS  -> not used
//   VCC   -> 3.3V
//   GND   -> GND
//   B+    -> Power + (6-28V)
//   B-    -> Power -
//   M+    -> Load +
//   M-    -> Load -
 
#include "mbed.h"
#include "IBT2.h"
 
IBT2 ibt(PTC10, PTC11, PTB11, 10000.0);    // L_pwm, R_pwm, en, freq
// manually enable the second enable line (R_EN)
DigitalOut R_en(PTB10);    // only because I used 2 wires
 
int main()
{
    // setup
    float speed = 0.0;
    float ds = 0.01;    // start ramping up
    R_en = 1;    // manually enable the R_EN line
    
    // loop
    while (true) {
        ibt.setSpeed(speed);
        
        // set up the next speed
        speed += ds;
        if (speed > 1.0f) {
            speed = 1.0;
            ds = -ds;    // stop at 1.0 and begin to ramp down
        } else if (speed < -1.0f) {
            speed = -1.0;
            ds = -ds;    // stop at -1.0 and begin to ramp up
        }
        
        wait(0.1);
    }
}
 