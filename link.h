//
// Include guard to stop link.h being loaded twice
#ifndef LINK_H
#define LINK_H

//
// The links a gateway can use, in the order it tries them
typedef enum
{
    MOBILE,
    LORA,
    SATELLITE,
} Link;

//
// Pick backup takes whether a LoRa neighbour is reachable and gives back the link to fail over to
Link pick_backup(int lora_neighbour_up);

//
// Link name takes a link and gives you the text
const char *link_name(Link l);

#endif