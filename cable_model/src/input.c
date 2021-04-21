#include "input.h"
#include "variables.h"

void read_values(struct cable *cable){
    char buffer[100];

    printf("model name: \n");
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%s", cable->name);
    }

    printf("length of the cable (%.0fmm): \n",cable->length*1000);
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%f", &cable->length);
        cable->length *= 0.001;
    }

    printf("radius (%.0fmm): \n",cable->radius*1000);
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%f", &cable->radius);
        cable->radius *= 0.001;
        cable->link.radius=cable->radius;
    }

    printf("number of elements (%d): \n",cable->nb_links);
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%d", &cable->nb_links);
    }


    printf("length of one element (%.0fmm) (override cable length): \n",cable->link.length*1000);
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%f", &cable->link.length);
        cable->link.length *= 0.001;
        cable->length = cable->link.length * cable->nb_links;
    }
    else
    {
        cable->link.length = cable->length / cable->nb_links;
    }

    printf("grasping point (%.0fmm): \n",cable->grasping_position*1000);
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%f", &cable->grasping_position);
        cable->grasping_position*=0.001;
        cable->grasping_link = cable->grasping_position / cable->link.length;
    }

    printf("density (%.0fkg/m³): \n",cable->density);
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%f", &cable->density);
    }


    printf("stiffness (%.4fN/m): \n",cable->joint.stiffness);
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%f", &cable->joint.stiffness);
    }

    printf("damping (%.4fN/m/s): \n",cable->joint.damping);
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%f", &cable->joint.damping);
    }

    printf("angle limit (180°): \n");
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        float angle_limit;
        sscanf(buffer, "%f", &angle_limit);
        cable->joint.u_limit = M_PI * angle_limit/180;
        cable->joint.l_limit = -cable->joint.u_limit;
    }

    //spring rigid mode
    printf("bent shape [y/n] (%d): \n",cable->mode.shape);
    char c_bent;
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%c", &c_bent);
    }

    if (c_bent == 'y')
    {
       cable->mode.shape = bent;
        printf("rigid spring reference (%.1f°): \n",cable->joint.reference *180/M_PI);
        if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
        {
            sscanf(buffer, "%f", &cable->joint.reference);
            cable->joint.reference = cable->joint.reference * M_PI/180;
        }

        printf("rigid ratio [0..1] (%.2f) : \n",cable->semi_rigid_ratio);
        if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
        {
            sscanf(buffer, "%f", &cable->semi_rigid_ratio);
        }
    }




    //change model name
    if (!strcmp(cable->name,""))
    {
        char mode_str[10]="";
        if (cable->mode.shape == bent)
        {strcat(mode_str,"bent_");}
        else {strcat(mode_str,"straight_");}

        if (cable->mode.force == torsion)
        {strcat(mode_str,"tor_");}

        if (cable->mode.rigid_end == external_dae )
        {strcat(mode_str,"ext");}

        sprintf(cable->name,"cable_l%.0f_r%.2f_nb%d_s%.4f_%s",
                cable->length*1000,
                cable->radius*1000,
                cable->nb_links,
                cable->joint.stiffness,
                mode_str);
    }
}


void calculate(struct cable *cable){

    //calculate inertial of a cylinder

    cable->link.mass = cable->density * M_PI * cable->link.length * cable->link.radius * cable->link.radius;


    cable->link.momentOfInertia.ixx = cable->link.mass/12 * (3 * cable->link.radius * cable->link.radius + cable->link.length * cable->link.length) ;
    cable->link.momentOfInertia.ixy = 0;
    cable->link.momentOfInertia.ixz = 0;
    cable->link.momentOfInertia.iyy = cable->link.momentOfInertia.ixx;
    cable->link.momentOfInertia.iyz = 0;
    cable->link.momentOfInertia.izz = cable->link.mass * cable->link.radius * cable->link.radius /2;
}

void read_intervals(struct interval *interval, int *execution_mode){

    char buffer[100];

    printf("select the variable to test (type the number, enter to quit):\n");
    printf("      0 cable's length\n      1 radius\n      2 number of elements\n"
           "      3 grasping point\n      4 element's length\n      5 density\n"
           "      6 stiffness\n      7 damping\n      8 angle limit\n"
           "      9 spring reference\n      10 semi rigid ratio\n");

    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        int selection;
        sscanf(buffer, "%d", &selection);
        interval->variable_test = selection;
        *execution_mode = MULTIPLE_MODELS;
    }
    else
    {
        return;
    }

    //set the unit
    switch (interval->variable_test) {
        case Cable_length:
        case Radius:
        case Grasping_point:
        case Link_length:
            sprintf(interval->unit,"mm");
            break;
        case Density:
            sprintf(interval->unit,"Kg/m³");
            break;
        case Stiffness:
            sprintf(interval->unit,"N/m");
            break;
        case Damping:
            sprintf(interval->unit,"N/m/s");
            break;
        case Angle_limit:
        case Spring_reference:
            sprintf(interval->unit,"°");
            break;
        case Semi_rigid_ratio:
            sprintf(interval->unit,"0..1");
            break;
        default:
            break;
    }

    //set the interval
    printf("set the interval's begin (%s):\n",interval->unit);
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%f", &interval->begin);
    }

    printf("set the interval's step (%s):\n",interval->unit);
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%f", &interval->step);
    }

    printf("set the number of models:\n");
    if ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (strcmp(buffer,"\n")))
    {
        sscanf(buffer, "%d", &interval->number);
    }

}