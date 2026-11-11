#ifndef MESSAGE_H
#define MESSAGE_H

// priority levels, lower number is more urgent
//
typedef enum
{
    CRITICAL,
    HIGH,
    ROUTINE,
    HEALTH,
} Priority;

// one reading sent by a gateway
//
typedef struct
{
    int gateway_id;
    int message_id;
    int water_level_cm;
    Priority priority;
} Message;

Priority get_priority(int rise_cm);
const char *priority_name(Priority p);

#endif