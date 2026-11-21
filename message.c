#include "message.h"

//
// How far the level is above normal, as a percentage
int percent_above_normal(int level_cm, int normal_cm)
{
    return (level_cm - normal_cm) * 100 / normal_cm;
}

//
// Thresholds
Priority get_priority(int percent_above)
{
    if (percent_above >= 65) return CRITICAL;
    if (percent_above >= 50) return HIGH;
    return ROUTINE;
}

//
// Minutes until the next reading, reads more often as the river rises
int get_interval(int percent_above)
{
    if (percent_above >= 65) return 3;
    if (percent_above >= 60) return 5;
    if (percent_above >= 50) return 10;
    return 15;
}

//
// Converts the enum to text for printing
const char *priority_name(Priority p)
{
    switch (p)
    {
    case CRITICAL: return "CRITICAL";
    case HIGH:     return "HIGH";
    case ROUTINE:  return "ROUTINE";
    case HEALTH:   return "HEALTH";
    }
    return "UNKNOWN";
}