#include "message.h"

// rise in cm since the last reading decides the priority
//
Priority get_priority(int rise_cm)
{
    if (rise_cm >= 15) return CRITICAL;
    if (rise_cm >= 5)  return HIGH;
    return ROUTINE;
}

// converts the enum to text for printing
//
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