#include "files.h"
#include "variables.h"

/**
 * Add the path of the executable
 * */

void find_path(char **argv, struct path *path){

    char path_save[PATH_MAX];
    char abs_exe_path[PATH_MAX];
    char *p;

    if(!(p = strrchr(argv[0], '/')))
        getcwd(abs_exe_path, sizeof(abs_exe_path));
    else
    {
        *p = '\0';
        getcwd(path_save, sizeof(path_save));
        chdir(argv[0]);
        getcwd(abs_exe_path, sizeof(abs_exe_path));
        chdir(path_save);
    }
    strcat(path->exe,abs_exe_path);
}

void add_files(struct path *path, struct cable cable) {

    //create a folder at the same path of the executable

    strcat(path->folder,path->exe);
    strcat(path->folder,"/");
    strcat(path->folder,cable.name);
    mkdir(path->folder, 0777);

    //new files
    strcat(path->sdf,path->folder);
    strcat(path->sdf,"/");
    strcat(path->sdf,"model.sdf");

    strcat(path->config,path->folder);
    strcat(path->config,"/");
    strcat(path->config,"model.config");

}

void clear_path(struct path *path){
    strcpy(path->folder,"");
    strcpy(path->sdf,"");
    strcpy(path->config,"");
}
