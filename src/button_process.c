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