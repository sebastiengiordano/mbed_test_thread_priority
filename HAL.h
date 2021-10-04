#ifndef HAL_H
#define HAL_H
#include "mbed.h"
//#include "mbed-trace/mbed_trace.h"


/* Enum*/
typedef enum{
    Enable,
    Disable
} eOutputState;


class HAL{

    public:
        HAL();

        /* Digital Output */
        void alert(eOutputState state);

        /* Backlight */ 
        void dark();

    private:

        /* PWM Output */
        void led_red(eOutputState state, uint16_t duty_cycle = 100);
        void led_green(eOutputState state, uint16_t duty_cycle = 100);
        void led_blue(eOutputState state, uint16_t duty_cycle = 100);

        /* Digital Output */
        DigitalOut  _alert;
        DigitalOut* _led_red_digital_out;
        DigitalOut* _led_green_digital_out;
        DigitalOut* _led_blue_digital_out;


        /* PWM Output */
        PwmOut* _led_red_pwm_out;
        PwmOut* _led_green_pwm_out;
        PwmOut* _led_blue_pwm_out;
};

#endif
