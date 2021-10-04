#include "mbed.h"


int main(int argc, char *argv[]){
    EventQueue* queue = mbed_event_queue();

    #ifdef DEBUG_MODE
        printf( "\n\n"
                "\t\t********\n"
                "\t\t* Main *\n"
                "\t\t********\n"
                "\n"
        );
        wait_us(1 * 1000);
    #endif

    /**************************/
    /* Threads Initialization */
    /**************************/




    /************************/
    /* Dispatch queue event */
    /************************/
    queue->dispatch_forever();

    return 0;
}
