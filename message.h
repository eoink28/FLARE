//
// Include guard to stop message.h being loaded twice
#ifndef MESSAGE_H
#define MESSAGE_H

//
// Priority levels, lower number is more urgent
// CRITICAL is 0, HIGH is 1, ROUTINE is 2, HEALTH is 3
typedef enum
{
    CRITICAL,
    HIGH,
    ROUTINE,
    HEALTH,
} Priority;

//
// One reading sent by a gateway
typedef struct
{
    int gateway_id;
    int message_id;
    int minute;
    int water_level_cm;
    int percent_above;
    Priority priority;
} Message;

//
// Percent above normal takes the level and the normal level and gives back how far above normal it is
int percent_above_normal(int level_cm, int normal_cm);

//
// Get priority takes the percent above normal and gives back a priority based on it
Priority get_priority(int percent_above);

//
// Get interval takes the percent above normal and gives back the minutes until the next reading
int get_interval(int percent_above);

//
// Priority name takes a priority and gives you the text
const char *priority_name(Priority p);

#endif