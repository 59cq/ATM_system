#include "tools.h"

void creatid(long* id){
    long id_buf;
    int fd = open("./data/id.dat",O_RDWR);
    read(fd,&id_buf,sizeof(id_buf));
    *id = id_buf;
    id_buf++;
    lseek(fd,0,0);
    write(fd,&id_buf,sizeof(id_buf));
    close(fd);
    return;
}



/************************************* */
bool add(User* use){
    creatid(&(use->userid));
    char path[100];
    sprintf(path,"./data/%ld.dat",use->userid);
    int fd = open(path,O_CREAT|O_EXCL|O_WRONLY,0777);
    if(0 > fd){
        return false;
    }
    write(fd,use,sizeof(User));
    close(fd);
    return true;
}

bool load(User* use){
    char path[100];
    sprintf(path,"./data/%ld.dat",use->userid);
    int fd = open(path,O_RDONLY);
    if(0 > fd){
        return false;
    }
    read(fd,use,sizeof(User));
    close(fd);
    return true;
}

bool save(User* use){
    char path[100];
    sprintf(path,"./data/%ld.dat",use->userid);
    int fd = open(path,O_WRONLY);
    if(0 > fd){
        return false;
    }
    lseek(fd,0,0);
    write(fd,use,sizeof(User));
    close(fd);
    return true;
}

bool delete(long userid){
    char path_o[100];
    char path_d[100];
    char cmd[200];
    sprintf(path_o,"./data/%ld.dat",userid);
    sprintf(path_d,"./data/backup/%ld.dat",userid);
    sprintf(cmd,"mv %s %s",path_o,path_d);
    system(cmd);
    return true;
}











