#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <button_interface.h>
#include <sys/types.h>
#include <signal.h>

#define _1ms    1000

bool Button_Run(void *object, char **argv, Button_Interface *button)
{
    int pidLed;

    if(argv[1][0] == '\0')
        return false;    

    if (button->Init(object) == false)
        return false;

    sscanf(argv[1], "%d", &pidLed);

    while (true)
    {
        while(true)
        {
            if(!button->Read(object)){
                usleep(_1ms * 100);
                kill(pidLed, SIGUSR1);
                break;
            }else{
                usleep( _1ms );
            }
        }
    }

    return false;
}
