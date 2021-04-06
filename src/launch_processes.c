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
    if(pidLed == 0)
    {        
        memset(args, 0, sizeof(args));        
        (void)execl("led_process", "led_process", NULL, (char *)0);
        exit(EXIT_FAILURE);
    }
    else if(pidLed > 0)
    {
        pidButton = fork();
        if(pidButton == 0)
        {            
            memset(args, 0, sizeof(args));
            sprintf(args, "%d", pidLed);
            (void)execl("button_process", "button_process", args, (char *)0);
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}