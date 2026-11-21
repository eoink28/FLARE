#include "link.h"

//
// LoRa through a neighbour first, satellite only as a last resort
Link pick_backup(int lora_neighbour_up)
{
    if (lora_neighbour_up) return LORA;
    return SATELLITE;
}

//
// Converts the enum to text for printing
const char *link_name(Link l)
{
    switch (l)
    {
    case MOBILE:    return "MOBILE";
    case LORA:      return "LORA";
    case SATELLITE: return "SATELLITE";
    }
    return "UNKNOWN";
}