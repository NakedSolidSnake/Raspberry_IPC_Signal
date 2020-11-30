#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <led.h>

void recv_sig(int sig){}

int main(int argc, char const *argv[])
{
    int state = 0;

    signal(SIGUSR1, recv_sig);    

     LED_t led =
    {
        .gpio.pin = 0,
        .gpio.eMode = eModeOutput
    };

     if (LED_init(&led))
        return EXIT_FAILURE;


    while(1)
    { 
        LED_set(&led, (eState_t)state);
        state ^= 0x01;
        pause();
        printf("Received signal\n");
    }
    
    return 0;
}