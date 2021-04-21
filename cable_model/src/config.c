#include "config.h"
#include "variables.h"

void write_config (struct path path, struct cable cable){

    FILE *file = fopen(path.config, "w");
    if (file == NULL)
    {
        printf("Could not open file");
        return ;
    }

    fprintf(file,"<?xml version=\"1.0\" ?>\n"
                  "<model>\n"
                  "    <name>%s</name>\n"
                  "    <version>1.0</version>\n"
                  "    <sdf version=\"1.6\">model.sdf</sdf>\n"
                  "    <author>\n"
                  "        <name>Abdelmajid Ouahchi</name>\n"
                  "        <email>ge69vun@mytum.de</email>\n"
                  "    </author>\n"
                  "    <description></description>\n"
                  "</model>",cable.name);

    fclose(file);
};