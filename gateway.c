#define SIZE 20

#include <stdio.h>
#include <unistd.h>  // used for the sleep function
#include "message.h"

int main(void)
{
    int water_level_cm = 100;
    int last_level_cm = 100;

    for (size_t i = 0; i < SIZE; i++)
    {
        Message msg;
        msg.gateway_id = 1;
        msg.message_id = i + 1;
        msg.water_level_cm = water_level_cm;
        msg.priority = get_priority(water_level_cm - last_level_cm);

        printf("[%s] ", priority_name(msg.priority)); // %s is for text
        printf("msg %d ", msg.message_id);
        printf("from gateway %d: ", msg.gateway_id);
        printf("%d cm\n", msg.water_level_cm);

        // simulation code, a flat river that rises slowly then fast
        //
        last_level_cm = water_level_cm;
        if (i < 3)      water_level_cm += 0;
        else if (i < 6) water_level_cm += 5;
        else            water_level_cm += 20;

        sleep(2);
    }

    return 0;
}