#include "sdf.h"
#include "variables.h"

void links (FILE *file, struct cable cable);
void joints (FILE *file, struct  cable cable);

 void write_sdf (struct path path, struct cable cable){
     //writing on file
     FILE *file = fopen(path.sdf, "w");
     if (file == NULL)
     {
         printf("Could not open file");
         return;
     }

     // first section: versions definition and model name
     fprintf(file,"<?xml version='1.0'?>\n"
                  "<sdf version='1.6'>\n" \
	  "<model name='%s'>\n",cable.name);




	  //links
    links(file,cable);

     //Joints
     joints(file,cable);

     //last section
     fprintf(file,"    <static>0</static>\n"
                  "    <allow_auto_disable>1</allow_auto_disable>\n"
                  "  </model>\n"
                  "</sdf>\n");

     fclose(file);
 }



 void links (FILE *file, struct cable cable){
     for(int i=0;i < cable.nb_links;i++)
     {
         //name of the link
         fprintf(file,"    <link name='link_%d'> \n",i);

         //inertial
         fprintf(file,"      <inertial>\n"
                      "        <mass>%e</mass>\n"
                      "        <inertia>\n"
                      "          <ixx>%e</ixx>\n"
                      "          <ixy>%e</ixy>\n"
                      "          <ixz>%e</ixz>\n"
                      "          <iyy>%e</iyy>\n"
                      "          <iyz>%e</iyz>\n"
                      "          <izz>%e</izz>\n"
                      "        </inertia>\n"
                      "        <pose frame=''>0 0 0 0 -0 0</pose>\n"
                      "      </inertial>\n",cable.link.mass,cable.link.momentOfInertia.ixx,
                 cable.link.momentOfInertia.ixy,cable.link.momentOfInertia.ixz,
                 cable.link.momentOfInertia.iyy,cable.link.momentOfInertia.iyz,cable.link.momentOfInertia.izz );

         //pose
         fprintf(file,"      <pose frame=''>0 0 %f 0 -0 0</pose>\n" , -i*cable.link.length);

         //gravity and self collision
         fprintf(file,"      <gravity>1</gravity>\n"
                      "      <self_collide>0</self_collide>\n");

         //make the grasped element fixed
         if (i == cable.grasping_link)
         {
             fprintf(file,"      <kinematic>1</kinematic>\n");
         }
         else
         {
             fprintf(file,"      <kinematic>0</kinematic>\n");
         }

         fprintf(file,"      <enable_wind>0</enable_wind>\n"
                      "      <visual name='visual'>\n"
                      "        <pose frame=''>0 0 0 0 -0 0</pose>\n"
                      "        <geometry>\n"
                      "          <cylinder>\n");

         fprintf(file,"            <radius>%f</radius>\n"
                      "            <length>%f</length>\n" , cable.link.radius, cable.link.length);

         fprintf(file,"          </cylinder>\n"
                      "        </geometry>\n"
                      "        <material>\n"
                      "          <lighting>1</lighting>\n"
                      "          <script>\n"
                      "            <uri>file://media/materials/scripts/gazebo.material</uri>\n"
                      "            <name>Gazebo/Grey</name>\n"
                      "          </script>\n"
                      "          <shader type='pixel'>\n"
                      "            <normal_map>__default__</normal_map>\n"
                      "          </shader>\n"
                      "          <ambient>0.5 0.75 0 1</ambient>\n"
                      "          <diffuse>1 1 0 1</diffuse>\n"
                      "          <specular>0.439 0.439 0.439 1</specular>\n"
                      "          <emissive>0.1 0 0.1 1</emissive>\n"
                      "        </material>\n"
                      "        <transparency>0</transparency>\n"
                      "        <cast_shadows>1</cast_shadows>\n"
                      "      </visual>\n"
                      "      <collision name='collision'>\n"
                      "        <laser_retro>0</laser_retro>\n"
                      "        <max_contacts>10</max_contacts>\n"
                      "        <pose frame=''>0 0 0 0 -0 0</pose>\n"
                      "        <geometry>\n"
                      "          <cylinder>\n");

         fprintf(file,"            <radius>%f</radius>\n"
                      "            <length>%f</length>\n" , cable.link.radius, cable.link.length);

         fprintf(file,"          </cylinder>\n"
                      "        </geometry>\n"
                      "        <surface>\n"
                      "          <friction>\n"
                      "            <ode>\n"
                      "              <mu>1</mu>\n"
                      "              <mu2>1</mu2>\n"
                      "              <fdir1>0 0 0</fdir1>\n"
                      "              <slip1>0</slip1>\n"
                      "              <slip2>0</slip2>\n"
                      "            </ode>\n"
                      "            <torsional>\n"
                      "              <coefficient>1</coefficient>\n"
                      "              <patch_radius>0</patch_radius>\n"
                      "              <surface_radius>0</surface_radius>\n"
                      "              <use_patch_radius>1</use_patch_radius>\n"
                      "              <ode>\n"
                      "                <slip>0</slip>\n"
                      "              </ode>\n"
                      "            </torsional>\n"
                      "          </friction>\n"
                      "          <bounce>\n"
                      "            <restitution_coefficient>0</restitution_coefficient>\n"
                      "            <threshold>1e+06</threshold>\n"
                      "          </bounce>\n"
                      "          <contact>\n"
                      "            <collide_without_contact>0</collide_without_contact>\n"
                      "            <collide_without_contact_bitmask>1</collide_without_contact_bitmask>\n"
                      "            <collide_bitmask>1</collide_bitmask>\n"
                      "            <ode>\n"
                      "              <soft_cfm>0</soft_cfm>\n"
                      "              <soft_erp>0.2</soft_erp>\n"
                      "              <kp>1e+13</kp>\n"
                      "              <kd>1</kd>\n"
                      "              <max_vel>0.01</max_vel>\n"
                      "              <min_depth>0</min_depth>\n"
                      "            </ode>\n"
                      "            <bullet>\n"
                      "              <split_impulse>1</split_impulse>\n"
                      "              <split_impulse_penetration_threshold>-0.01</split_impulse_penetration_threshold>\n"
                      "              <soft_cfm>0</soft_cfm>\n"
                      "              <soft_erp>0.2</soft_erp>\n"
                      "              <kp>1e+13</kp>\n"
                      "              <kd>1</kd>\n"
                      "            </bullet>\n"
                      "          </contact>\n"
                      "        </surface>\n"
                      "      </collision>\n"
                      "    </link>\n");
     }
 }

void joints (FILE *file, struct cable cable) {
    for (int i = 0; i < cable.nb_links-1; i++)
    {
//joint name
        fprintf(file,"    <joint name='link_%d_link_%dJOINT_%d' type='universal'>\n",i,i+1,i);
        //Parent and child
        fprintf(file,"      <parent>link_%d</parent>\n"
                     "      <child>link_%d</child>\n", i, i+1);

        //joint pose
        fprintf(file,"      <pose frame=''>0 0 %f 0 -0 0</pose>\n", cable.link.length/2);

        //axis parameters
        fprintf(file,"      <axis>\n"
                     "        <xyz>1 0 0</xyz>\n"
                     "        <use_parent_model_frame>0</use_parent_model_frame>\n"
                     "        <limit>\n");

        fprintf(file,"          <lower>%e</lower>\n"
                     "          <upper>%e</upper>\n",  cable.joint.l_limit,cable.joint.u_limit);

        fprintf(file,"          <effort>-1</effort>\n"
                     "          <velocity>-1</velocity>\n"
                     "        </limit>\n"
                     "        <dynamics>\n");

        //Semi rigid mode
        if ( (cable.mode.shape == bent) && (i > (cable.nb_links * (1 - cable.semi_rigid_ratio))))
        {
            fprintf(file,"          <spring_reference>%f</spring_reference>\n" ,cable.joint.reference);
        }
        else
        {
            fprintf(file,"          <spring_reference>0</spring_reference>\n");
        }

        fprintf(file,"          <spring_stiffness>%f</spring_stiffness>\n"
                     "          <damping>%f</damping>\n",cable.joint.stiffness, cable.joint.damping);

        fprintf(file,"          <friction>0</friction>\n"
                     "        </dynamics>\n"
                     "      </axis>\n"
                     "      <axis2>\n"
                     "        <xyz>0 1 0</xyz>\n"
                     "        <use_parent_model_frame>0</use_parent_model_frame>\n"
                     "        <dynamics>\n");

        //Spring rigid mode
        /*if ((rigid_mode) && (i > number_of_elements*rigid_ratio))
        {
            fprintf(file,"          <spring_reference>%f</spring_reference>\n" ,spring_reference_rigid);
        }
            else  */
        {
            fprintf(file,"          <spring_reference>0</spring_reference>\n" );
        }

        fprintf(file,"          <spring_stiffness>%f</spring_stiffness>\n"
                     "          <damping>%f</damping>\n",cable.joint.stiffness, cable.joint.damping);


        fprintf(file,"          <friction>0</friction>\n"
                     "        </dynamics>\n"
                     "        <limit>\n");

        fprintf(file,"          <lower>%e</lower>\n"
                     "          <upper>%e</upper>\n",  cable.joint.l_limit,cable.joint.u_limit);

        fprintf(file,"          <effort>-1</effort>\n"
                     "          <velocity>-1</velocity>\n"
                     "        </limit>\n"
                     "      </axis2>\n"
                     "      <physics>\n"
                     "        <ode>\n"
                     "            <implicit_spring_damper>1</implicit_spring_damper>\n"
                     "            <cfm>0</cfm>\n"
                     "            <erp>1</erp>\n"
                     "          <limit>\n"
                     "            <cfm>0</cfm>\n"
                     "            <erp>0.2</erp>\n"
                     "          </limit>\n"
                     "          <suspension>\n"
                     "            <cfm>0</cfm>\n"
                     "            <erp>0.2</erp>\n"
                     "          </suspension>\n"
                     "        </ode>\n"
                     "      </physics>\n"
                     "    </joint>\n");
    }

}