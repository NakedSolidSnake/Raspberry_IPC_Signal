<p align="center">
  <img src="https://cdn0.sbnation.com/assets/3417793/moveoverlynnswann.gif"/>
</p>

# Signal
## Introdução
## Implementação
### launch_process.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    
    int pidLed;
    int pidButton;
    char args[BUFSIZ + 1];    
    

    
    pidLed = fork();
    if(pidLed == 0){        
        memset(args, 0, sizeof(args));        
        (void)execl("led_process", "led_process", NULL, (char *)0);
        exit(EXIT_FAILURE);
    }else if(pidLed > 0){
        pidButton = fork();
        if(pidButton == 0){            
            memset(args, 0, sizeof(args));
            sprintf(args, "%d", pidLed);
            (void)execl("button_process", "button_process", args, (char *)0);
            exit(EXIT_FAILURE);
        }
    }
    

    return 0;
}
```
### button_process.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <button.h>
#include <sys/types.h>
#include <signal.h>

#define _1ms    1000

static Button_t button = {
    .gpio.pin = 7,
    .gpio.eMode = eModeInput,
    .ePullMode = ePullModePullUp,
    .eIntEdge = eIntEdgeFalling,
    .cb = NULL};

int main(int argc, char const *argv[])
{
    int pidLed;

    if(argc != 2)
        return EXIT_FAILURE;

    sscanf(argv[1], "%d", &pidLed);

    if (Button_init(&button))
        return EXIT_FAILURE;

    while (1)
    {
        if (!Button_read(&button))
        {
            usleep(_1ms * 40);
            while (!Button_read(&button))
                ;
            usleep(_1ms * 40);
            kill(pidLed, SIGUSR1);
            usleep(500 * _1ms);
        }
        else
        {
            usleep(_1ms);
        }
    }

    return 0;
}
```
### led_process.c
```c
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
```
## Conclusão
