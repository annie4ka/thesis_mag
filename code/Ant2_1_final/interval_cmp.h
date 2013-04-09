#ifndef INTERVAL_CMP_H
#define INTERVAL_CMP_H
#include "intervals.h"
bool operator== (ant_interval i1, ant_interval i2);
bool operator< (ant_interval i1, ant_interval i2);

bool operator<= (ant_interval i1, ant_interval i2);

bool operator>(ant_interval i1, ant_interval i2);

bool operator>=(ant_interval i1, ant_interval i2);

bool operator!= (ant_interval i1, ant_interval i2);

#endif // INTERVAL_CMP_H
