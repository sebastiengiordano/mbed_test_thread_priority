#include "HAL.h"
#include "PinNames.h"
#include "BMS_Parameters.h"


/***************/
/* Constructor */
/***************/
HAL::HAL() :

        // BMS signals namings          (STM32L0xxk6/8 LQFP32 pinout)
    _alert(ALERT, 0)

    {
    /***************************************/
    /* Digital Output set to idle position */
    /***************************************/
    _alert                               = 0;

    /**************************/
    /* Pointer initialization */
    /**************************/
    _led_red_digital_out                = NULL;
    _led_green_digital_out              = NULL;
    _led_blue_digital_out               = NULL;
    _led_red_pwm_out                    = NULL;
    _led_green_pwm_out                  = NULL;
    _led_blue_pwm_out                   = NULL;


    // Led set to off
    dark();
}


/*****************/
/* Public method */
/*****************/

void HAL::alert(eOutputState state){
    // This function aims to set the ALERT ouput:
    //      Enable  : stop LEDs display, turn off the step up then cut the power.
    //      Disable : maintain the power.
    #ifdef DEBUG_MODE_CALL
        printf("HAL::alert\t\t\t\tCall.\n");
        wait_us(10 * 1000);
    #endif
    
    if (state == Enable) {
        dark();
        step_up_choice(Disable);
        _alert = 1;
    }
    else {
        _alert = 0;
    }
}


/*************/
/* Backlight */
/*************/

void HAL::dark(){
    led_red(Disable);
    led_green(Disable);
    led_blue(Disable);
}


/******************/
/* Private method */
/******************/

/* PWM Output */
void HAL::led_red(eOutputState state, uint16_t duty_cycle){
    if (state == Enable) {
        if (_led_red_pwm_out != NULL){
            delete _led_red_pwm_out;
            _led_red_pwm_out = NULL;
        }
        _led_red_pwm_out = new PwmOut(LED_R);
        _led_red_pwm_out->period_ms(PWM_PERIODE);
        _led_red_pwm_out->pulsewidth_us((100 - duty_cycle) * PWM_PERIODE * 10);
    }
    else {
        if (_led_red_pwm_out != NULL){
            delete _led_red_pwm_out;
            _led_red_pwm_out = NULL;
        }
        delete _led_red_digital_out;
        _led_red_digital_out = new DigitalOut(LED_R);
        *_led_red_digital_out = 1;
    }
}

void HAL::led_green(eOutputState state, uint16_t duty_cycle){
    if (state == Enable) {
        if (_led_green_pwm_out != NULL){
            delete _led_green_pwm_out;
            _led_green_pwm_out = NULL;
        }
        _led_green_pwm_out = new PwmOut(LED_G);
        _led_green_pwm_out->period_ms(PWM_PERIODE);
        _led_green_pwm_out->pulsewidth_us((100 - duty_cycle) * PWM_PERIODE * 10);
    }
    else {
        if (_led_green_pwm_out != NULL){
            delete _led_green_pwm_out;
            _led_green_pwm_out = NULL;
        }
        delete _led_green_digital_out;
        _led_green_digital_out = new DigitalOut(LED_G);
        *_led_green_digital_out = 1;
    }
}

void HAL::led_blue(eOutputState state, uint16_t duty_cycle){
    if (state == Enable) {
        if (_led_blue_pwm_out != NULL){
            delete _led_blue_pwm_out;
            _led_blue_pwm_out = NULL;
        }
        _led_blue_pwm_out = new PwmOut(LED_B);
        _led_blue_pwm_out->period_ms(PWM_PERIODE);
        _led_blue_pwm_out->pulsewidth_us((100 - duty_cycle) * PWM_PERIODE * 10);
    }
    else {
        if (_led_blue_pwm_out != NULL){
            delete _led_blue_pwm_out;
            _led_blue_pwm_out = NULL;
        }
        delete _led_blue_digital_out;
        _led_blue_digital_out = new DigitalOut(LED_B);
        *_led_blue_digital_out = 1;
    }
}