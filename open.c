#include "mytypes.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <getch.h>
#include <fcntl.h>
#include "msg_queue.h"
#include "tools.h"


/*
int main(){
    int fd = open("./data/id.dat",O_CREAT|O_EXCL|O_RDWR,0777);
    long id = 20190801;
    write(fd,&id,sizeof(id));
    close(fd);
}
*/



int main(){

    int msgid_cs = getmsgid_cs();
    int msgid_sc = getmsgid_sc();
    Ackbuf ack;
    Msgbuf msg;
    User use;
    while(1){
    
        msgrcv(msgid_cs,&msg,sizeof(Msgbuf),MSG_OPEN,0);
        ack.mtype = msg.pid;
        strcpy(use.id,msg.id);
        use.lock = 0;
        use.money - 0;
        strcpy(use.pswd,msg.pswd);
        if(add(&use)){
            ack.tf = true;
            sprintf(ack.msg,"\033[34;40m%ld\033[0m",use.userid);
        }else{
            ack.tf = false;
            strcpy(ack.msg,"creat file err");
        }
        msgsnd(msgid_sc,&ack,sizeof(Ackbuf)-sizeof(ack.mtype),0);
    }

    

}
 



