#ifndef _ARRIVAL_CURVE_H_
#define _ARRIVAL_CURVE_H_

#define DEVICE_ID 0

//O(mn) solution (m = time interval size, n = event size)
typedef struct step {
        float events;
        float left;
        float right;
} step;

#endif
