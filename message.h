#ifndef MESSAGE_H //include guard to stop message.h being loaded twice.
#define MESSAGE_H

// priority levels, lower number is more urgent
//
typedef enum
{
    CRITICAL, //0
    HIGH, //1
    ROUTINE, //2
    HEALTH, //3
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

//get priority which takes the rise in and gives back a priority based on this rise
//
Priority get_priority(int rise_cm);

//priority name gives a priority and gives you the text
//
const char *priority_name(Priority p);

#endif