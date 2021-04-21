#include "variables.h"
#include "input.h"
#include "files.h"
#include "sdf.h"
#include "config.h"
#include "multiple.h"
#include "main.h"

int execution_mode = SINGLE_MODEL;

//initialize the intervals
struct interval interval={Nb_links,15,1,5,""};

//initialize the path
struct path path = {"","","",""};

//set default values for the cable model
struct cable cable ={.name="",
        .length=0.300,
        .density=4500,
        .radius=0.004,
        .semi_rigid_ratio=1,
        .nb_links=15,
        .grasping_link=0,
        .grasping_position=0,
        .mode={bent,no_torsion,normal},
        .joint={.stiffness=1,
                .damping=1,
                .u_limit=1.79769e+308,
                .l_limit=-1.79769e+308,
                .reference=20 * M_PI/180},
        .link={.length=0.02,
               .radius=0.004,
               .mass=0,
               .momentOfInertia={0,0,0,0,0,0}}};

int main(int argc, char **argv){

    find_path(argv,&path);
    read_values(&cable);
    calculate(&cable);
    read_intervals(&interval,&execution_mode);

    if (execution_mode == SINGLE_MODEL)
    {
        add_files(&path,cable);
        write_sdf(path,cable);
        write_config(path,cable);
    }
    else
    {
        printf("variable test: %d\n",interval.variable_test);
        printf("begin: %f\n",interval.begin);
        printf("step: %f\n",interval.step);
        printf("number: %d\n",interval.number);
        printf("unit: %s\n",interval.unit);


        //initialize multiple cables
        struct cable * cables;
        initialize(cable,&cables,interval);
        add_interval(&cables,interval);

        for (int i = 0; i < interval.number; ++i) {
            calculate(&cables[i]);
            add_files(&path,cables[i]);
            write_sdf(path,cables[i]);
            write_config(path,cables[i]);
            clear_path(&path);
        }



        /*for testing
         *
         * struct cable cable1 = cable;
        strcat(cable1.name,"theni");

        add_files(&path,cable);
        //write_sdf(path,cable);
        //write_config(path,cable);

        printf("first path exe: %s\n",path.exe);
        printf("first path folder: %s\n",path.folder);
        printf("first path sdf: %s\n",path.sdf);
        printf("first path config: %s\n",path.config);

        clear_path(&path);

        add_files(&path,cable1);
        //write_sdf(path,cable1);
        //write_config(path,cable1);

        printf("second path exe: %s\n",path.exe);
        printf("second path folder: %s\n",path.folder);
        printf("second path sdf: %s\n",path.sdf);
        printf("second path config: %s\n",path.config);
         *
         */



    }



    return 0;
}