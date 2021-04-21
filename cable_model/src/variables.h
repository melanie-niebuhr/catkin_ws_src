#ifndef VARIABLES_H_
#define VARIABLES_H_

#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>


//mode of execution
#define SINGLE_MODEL 0
#define MULTIPLE_MODELS 1

//conversions
#define PI (3.1415926535897932384626433832f)
#define M_TO_MM 1000
#define MM_TO_M 0.001
#define RAD_TO_DEG (180.0f/PI)
#define DEG_TO_RAD (PI/180.0f)


struct path
{
    char exe[PATH_MAX];
    char folder[PATH_MAX];
    char sdf[PATH_MAX];
    char config[PATH_MAX];
};

struct interval
{
    enum variable_test {
        Cable_length,
        Radius,
        Nb_links,
        Grasping_point,
        Link_length,
        Density,
        Stiffness,
        Damping,
        Angle_limit,
        Spring_reference,
        Semi_rigid_ratio
    }variable_test;
    float begin;
    float step;
    int number;
    char unit[10];
};

struct joint
{
    float stiffness;
    float damping;
    float u_limit;
    float l_limit;
    float reference;
};

struct moment_of_inertia
{
    double ixx;
    double ixy;
    double ixz;
    double iyy;
    double iyz;
    double izz;
};

struct link
{
    float length;
    float radius;
    double mass;
    struct moment_of_inertia momentOfInertia;
};

struct mode
{
    enum shape {straight, bent}shape;
    enum force {torsion, no_torsion}force;
    enum rigid_end {external_dae, normal}rigid_end;
};

struct cable
{
    char name[70];
    float length;
    float density;
    float radius;
    float semi_rigid_ratio;
    float grasping_position;
    int nb_links;
    int grasping_link;
    struct link link;
    struct joint joint;
    struct mode mode;
};



extern struct path path;
extern struct cable cable;
extern struct interval interval;
extern int execution_mode;



#endif
