#include "multiple.h"
#include "variables.h"

void initialize(struct cable cable, struct cable *cables[50], struct interval interval){

    char tmp[3];
    for (int i=0; i<interval.number; i++)
    {

        *cables[i] = cable;

        //change the name
        sprintf(tmp,"%d",i);
        strcat(tmp,cables[i]->name);
        strcpy(cables[i]->name,tmp);



/*
        //model characteristics
        sprintf(cables[i]->name,"%d",i);

        cables[i]->length=0.600;
        cables[i]->density=4500;
        cables[i]->radius=0.004;
        cables[i]->semi_rigid_ratio=1;
        cables[i]->nb_links=30;
        cables[i]->grasping_link=0;
        cables[i]->grasping_position=0;
        //mode
        cables[i]->mode.shape=bent;
        cables[i]->mode.force=no_torsion;
        cables[i]->mode.rigid_end=normal;
        //joint
        cables[i]->joint.stiffness=0.5;
        cables[i]->joint.damping=0.5;
        cables[i]->joint.u_limit=1.79769e+308;
        cables[i]->joint.l_limit=-1.79769e+308;
        cables[i]->joint.reference=20 * M_PI/180;
        //link
        cables[i]->link.length=0.02;
        cables[i]->link.radius=0.004;
        cables[i]->link.mass=0;
        */

    }
}

void add_interval(struct cable *cables[50], struct interval interval){

    for (int i=0; i<interval.number; i++)
    {
        switch (interval.variable_test) {
            case Cable_length:
                cables[i]->length = interval.begin + i * interval.step;
                cables[i]->length *= MM_TO_M;
                cables[i]->link.length = cables[i]->length / cables[i]->nb_links;
                break;
            case Radius:
                cables[i]->radius = interval.begin + i * interval.step;
                cables[i]->radius *= MM_TO_M;
                cables[i]->link.radius = cables[i]->radius;
                break;
            case Nb_links:
                cables[i]->nb_links = interval.begin + i * interval.step;
                break;
            case Grasping_point:
                cables[i]->grasping_position = interval.begin + i * interval.step;
                cables[i]->grasping_position *= MM_TO_M;
                break;
            case Link_length:
                cables[i]->link.length = interval.begin + i * interval.step;
                cables[i]->link.length *= MM_TO_M;
                cables[i]->length = cables[i]->link.length * cables[i]->nb_links;
                break;
            case Density:
                cables[i]->density = interval.begin + i * interval.step;
                break;
            case Stiffness:
                cables[i]->joint.stiffness = interval.begin + i * interval.step;
                break;
            case Damping:
                cables[i]->joint.damping = interval.begin + i * interval.step;
                break;
            case Angle_limit:
                cables[i]->joint.u_limit = interval.begin + i * interval.step;
                cables[i]->joint.u_limit *= DEG_TO_RAD;
                cables[i]->joint.l_limit = -cables[i]->joint.u_limit;
                break;
            case Spring_reference:
                cables[i]->joint.reference = interval.begin + i * interval.step;
                cables[i]->joint.reference *= DEG_TO_RAD;
                break;
            case Semi_rigid_ratio:
                cables[i]->semi_rigid_ratio = interval.begin + i * interval.step;
                break;
        }
    }
}