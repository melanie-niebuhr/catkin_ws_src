#ifndef FILES_H_
#define FILES_H_

#include "variables.h"

void find_path(char **argv, struct path *path);
void add_files(struct path *path, struct cable cable);
void clear_path(struct path *path);


#endif