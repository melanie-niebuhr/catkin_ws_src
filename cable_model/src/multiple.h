#ifndef MULTIPLE_H_
#define MULTIPLE_H_

#include "variables.h"

void initialize(struct cable cable, struct cable *cables[50], struct interval interval);
void add_interval(struct cable *cables[50], struct interval interval);

#endif