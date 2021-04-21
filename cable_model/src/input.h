#ifndef INPUT_H_
#define INPUT_H_

#include "variables.h"

void read_values (struct cable *cable);
void calculate (struct cable *cable);
void read_intervals(struct interval *interval, int *execution_mode);

#endif