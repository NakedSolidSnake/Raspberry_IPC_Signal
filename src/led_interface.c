#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <led_interface.h>

void recv_sig(int sig){}

bool LED_Run(void *object, LED_Interface *led)
{
    int state = 0;

    signal(SIGUSR1, recv_sig);    


    if (led->Init(object) == false)
        return false;


    while(true)
    { 
        led->Set(object, (uint8_t)state);
        state ^= 0x01;
        pause();
    }
    return false;
}
