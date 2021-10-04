#include "mbed.h"
#include "HAL.h"
#include "thread_main_priority.h"

Thread thread;


int main(int argc, char *argv[]){

    #ifdef DEBUG_MODE
        printf( "\n\n"
                "\t\t********\n"
                "\t\t* Main *\n"
                "\t\t********\n"
                "\n"
        );
        wait_us(1 * 1000);
    #endif

    /**************************************************/
    /* Continuity of microcontroller electrical power */
    /**************************************************/
    DigitalOut  micro_electrical_power(ALERT, 0);

    /*********************************************/
    /* Hardware Abstraction Layer Initialization */
    /*********************************************/
    HAL    hal;

    /**************************/
    /* Threads Initialization */
    /**************************/

    /*****************/
    /* Threads start */
    /*****************/
    thread.start(callback(blink, &led1));
    ThisThread::sleep_for(5000);
    thread.join();

    return 0;
}
