#include "mbed.h"
#include "HAL.h"
#include "thread_main_priority.h"


Ticker ticker;
Thread thread;
Queue<const char *, 5> trail;


// Since we're printing from multiple threads, we need a mutex
Mutex print_lock;


enum ExecutionTypes {
    IDLE,
    USER,
    ISR
};


const char *ExecutionMessages[] = {
    "the idle thread",
    "a user thread",
    "interrupt context"
};


void handler(uint16_t delay)
{
    // Safe to print
    print_lock.lock();
    printf("  Starting %s \t %d \t priority: %d \t sleep_for: %d\n",
            ThisThread::get_name(),
            ThisThread::get_id(),
            ThisThread::get_priority(),
            delay);
    print_lock.unlock();

    while (true) {
        print_lock.lock();
        printf(
            "\t %s \t id: %d \t priority: %d \t sleep_for: %d\n",
            ThisThread::get_name(),
            ThisThread::get_id(),
            ThisThread::get_priority(),
            delay);
        printf("Execution was in %s\r\n", *(const char **)evt.value.v);
        print_lock.unlock();
        ThisThread::sleep_for(chrono::milliseconds(delay));

        
        print_lock.lock();
        printf(
            "\t %s \t id: %d \t priority: %d \t wait_us: 1000 ms\n",
            ThisThread::get_name(),
            ThisThread::get_id(),
            ThisThread::get_priority()
            );
        printf("Execution was in %s\r\n", *(const char **)evt.value.v);
        print_lock.unlock();
        wait_us(1000 * 1000);
    }
}


int main(int argc, char *argv[]){

    /**************************************************/
    /* Continuity of microcontroller electrical power */
    /**************************************************/
    DigitalOut  micro_electrical_power(ALERT, 0);

    #ifdef DEBUG_MODE
        printf( "\n\n"
                "\t\t********\n"
                "\t\t* Main *\n"
                "\t\t********\n"
                "\n"
        );
        wait_us(1 * 1000);
    #endif


    /*********************************************/
    /* Hardware Abstraction Layer Initialization */
    /*********************************************/
    HAL    hal;


    /******************/
    /* Initialization */
    /******************/
    Thread *ThreadPriorityLow = new Thread(osPriorityLow, 512, NULL, "osPriorityLow");
    Thread *ThreadPriorityBelowNormal = new Thread(osPriorityBelowNormal, 512, NULL, "osPriorityBelowNormal");
    Thread *ThreadPriorityNormal1 = new Thread(osPriorityNormal1, 512, NULL, "ThreadPriorityNormal1");
    Thread *ThreadPriorityNormal6 = new Thread(osPriorityNormal6, 512, NULL, "ThreadPriorityNormal6");
    Thread *ThreadPriorityAboveNormal = new Thread( osPriorityAboveNormal, 512, NULL, "ThreadPriorityAboveNormal");
    Thread *ThreadPriorityHigh3 = new Thread(osPriorityHigh3, 512, NULL, "ThreadPriorityHigh3");
    Thread *ThreadPriorityHigh5 = new Thread(osPriorityHigh5, 512, NULL, "ThreadPriorityHigh5");
    Thread *ThreadPriorityRealtime = new Thread(osPriorityRealtime, 512, NULL, "osPriorityRealtime");
    Thread *ThreadPriorityRealtime7 = new Thread(osPriorityRealtime7, 512, NULL, "osPriorityRealtime7");


    /*****************/
    /* Threads start */
    /*****************/

    // Start the user thread
    ThreadPriorityLow->start(callback(thread_priority_normal, 100));
    wait(0.01);
    ThreadPriorityBelowNormal->start(callback(thread_priority_normal, 200));
    wait(0.01);
    ThreadPriorityNormal1->start(callback(thread_priority_normal, 300));
    wait(0.01);
    ThreadPriorityNormal6->start(callback(thread_priority_normal, 400));
    wait(0.01);
    ThreadPriorityAboveNormal->start(callback(thread_priority_normal, 500));
    wait(0.01);
    ThreadPriorityHigh3->start(callback(thread_priority_normal, 600));
    wait(0.01);
    ThreadPriorityHigh5->start(callback(thread_priority_normal, 700));
    wait(0.01);
    ThreadPriorityRealtime->start(callback(thread_priority_normal, 800));
    wait(0.01);
    ThreadPriorityRealtime7->start(callback(thread_priority_normal, 1000));
    wait(0.01);


    ThisThread::sleep_for(5s);
    // Wait for the thread to terminate
    thread.join();

    return 0;
}
