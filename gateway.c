#define NORMAL_LEVEL_CM 100
#define PEAK_LEVEL_CM 182
#define SIM_MINUTES 230
#define MAX_MISSES 3
#define STORM_START_MIN 150
#define STORM_END_MIN 200
#define LORA_NEIGHBOUR_UP 1

#include <stdio.h>
#include <unistd.h>
#include "message.h"
#include "link.h"

int main(void)
{
    int water_level_mm = NORMAL_LEVEL_CM * 10;
    int rise_mm = 1;
    int next_reading = 0;
    int message_id = 1;

    Link current_link = MOBILE;
    int missed_acks = 0;
    int sent = 0;
    int not_delivered = 0;

    //
    // One loop is 30 seconds, the time between heartbeats
    for (int tick = 0; tick <= SIM_MINUTES * 2; tick++)
    {
        int minute = tick / 2;
        int seconds = (tick % 2) * 30;

        //
        // The storm knocks out the mobile network between these times
        int mobile_up = !(minute >= STORM_START_MIN && minute < STORM_END_MIN);

        if (tick == STORM_START_MIN * 2) printf("\n*** STORM: mobile network down at %d:00 ***\n\n", STORM_START_MIN);
        if (tick == STORM_END_MIN * 2) printf("\n*** Mobile network back at %d:00 ***\n\n", STORM_END_MIN);

        //
        // Heartbeat over the mobile network every 30 seconds
        if (mobile_up)
        {
            missed_acks = 0;
            if (current_link != MOBILE)
            {
                current_link = MOBILE;
                printf("RECOVERY at %d:%02d: switching back to MOBILE\n", minute, seconds);
            }
        }
        else if (current_link == MOBILE)
        {
            missed_acks++;
            printf("Heartbeat missed at %d:%02d (%d/%d)\n", minute, seconds, missed_acks, MAX_MISSES);

            //
            // After 3 missed replies the mobile link is treated as down
            if (missed_acks >= MAX_MISSES)
            {
                current_link = pick_backup(LORA_NEIGHBOUR_UP);
                printf("FAILOVER at %d:%02d: switching to %s\n", minute, seconds, link_name(current_link));
            }
        }

        //
        // Take a reading when it is due
        if (tick == next_reading * 2)
        {
            Message msg;
            msg.gateway_id = 1;
            msg.message_id = message_id++;
            msg.minute = minute;
            msg.water_level_cm = water_level_mm / 10;
            msg.percent_above = percent_above_normal(msg.water_level_cm, NORMAL_LEVEL_CM);
            msg.priority = get_priority(msg.percent_above);

            int interval = get_interval(msg.percent_above);

            //
            // %s is for text
            printf("[%s] ", priority_name(msg.priority));
            printf("minute %d, msg %d: ", msg.minute, msg.message_id);
            printf("%d cm (%d%% above normal), ", msg.water_level_cm, msg.percent_above);

            //
            // A reading sent on mobile before the outage is noticed gets no reply
            if (current_link == MOBILE && !mobile_up)
            {
                printf("NOT DELIVERED (no ACK)\n");
                not_delivered++;
            }
            else
            {
                printf("sent via %s\n", link_name(current_link));
                sent++;
            }

            next_reading = minute + interval;

            //
            // Add a 1 second delay in between messages
            sleep(1);
        }

        //
        // Simulation code, a flat river that rises slowly then fast
        // The rise doubles every 40 minutes until the peak
        if (seconds == 0)
        {
            if (minute > 0 && minute % 40 == 0) rise_mm = rise_mm * 2;
            if (water_level_mm < PEAK_LEVEL_CM * 10) water_level_mm += rise_mm;
        }
    }

    printf("\nReadings sent: %d, not delivered: %d\n", sent, not_delivered);

    return 0;
}